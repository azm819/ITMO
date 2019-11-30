#include "worker.h"

#include <QFile>
#include <QTextStream>
#include <QThread>

#include <iostream>

#include "utils.h"

Worker::Worker(std::vector<QString>& paths, bool preprocess) : _preprocess(preprocess) {
    for (auto &path: paths) {
        QFile file(path);
        if (!file.open(QFile::ReadOnly)) {
            emit throwError(path + ": is not readable");
            return;
        }
        _trigrammHolders.emplace_back(path);
        file.close();
    }
}

void Worker::processFiles() {
    if (_preprocess) {
        for (auto &trigrammHolder: _trigrammHolders) {
            if (QThread::currentThread()->isInterruptionRequested()) {
                break;
            }
            QFile file(trigrammHolder._path);
            file.open(QFile::ReadOnly);
            QTextStream stream(&file);
            QString buffer = stream.readLine(BUFFER_SIZE);
            while (buffer.size() > 3) {
                if (QThread::currentThread()->isInterruptionRequested()) {
                    break;
                }
                uint64_t trigramm = (static_cast<uint64_t>( buffer[0].unicode()) << SMALL_SHIFT) + (static_cast<uint64_t> (buffer[1].unicode()) << BIG_SHIFT);
                for (int i = 2; i < buffer.size(); ++i) {
                    if (QThread::currentThread()->isInterruptionRequested()) {
                        break;
                    }
                    trigramm = (trigramm >> SMALL_SHIFT) + (static_cast<uint64_t> (buffer[i].unicode()) << BIG_SHIFT);
                    trigrammHolder._trigramms.insert(trigramm);
                }
                buffer = stream.readLine(BUFFER_SIZE);
            }
            file.close();
        }
    }
}

void Worker::defaultSearching(QString &path) {
    auto coor = searchInFile(path, _searcher.get());
    if (coor.size() > 0) {
        qRegisterMetaType<std::vector<std::pair<int, int>>>("coor");
        emit throwMatch(path, coor);
    } else {
        emit throwNoMatch(path);
    }
}

void Worker::findSubString(QString subString) {
    _searcher.reset(new std::boyer_moore_horspool_searcher<QChar*, std::hash<QChar>, std::equal_to<void>>(subString.begin(), subString.end()));
    if (subString.size() < 3 || !_preprocess) {
        for (auto &trigrammHolder: _trigrammHolders) {
            if (QThread::currentThread()->isInterruptionRequested()) {
                break;
            }
            defaultSearching(trigrammHolder._path);
        }
        return;
    }
    std::vector<uint64_t> myTrigramms;
    uint64_t trigramm = (static_cast<uint64_t>(subString[0].unicode()) << SMALL_SHIFT) + (static_cast<uint64_t>(subString[1].unicode()) << BIG_SHIFT);
    for (int i = 2; i < subString.size(); ++i) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            break;
        }
        trigramm = (trigramm >> SMALL_SHIFT) + (static_cast<uint64_t>(subString[i].unicode()) << BIG_SHIFT);
        myTrigramms.push_back(trigramm);
    }
    for (TrigrammHolder &trigrammHolder: _trigrammHolders) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            break;
        }
        bool possible = true;
        for (uint64_t &trig: myTrigramms) {
            if (QThread::currentThread()->isInterruptionRequested()) {
                break;
            }
            if (trigrammHolder._trigramms.find(trig) == trigrammHolder._trigramms.end()) {
                possible = false;
                break;
            }
        }
        if (possible) {
            defaultSearching(trigrammHolder._path);
        } else {
            emit throwNoMatch(trigrammHolder._path);
        }
    }
}

Worker::TrigrammHolder::TrigrammHolder(QString &path) : _path(path) {}
