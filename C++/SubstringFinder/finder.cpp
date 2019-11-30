#include "finder.h"

#include <QFileInfo>
#include <QThread>

#include <iostream>

Finder::Finder(bool hiddenMode, bool recursiveMode, bool preprocessMode) : _preprocessMode(preprocessMode), _totalSize(0),  _processedSize(0) {
    _iterationFlags = recursiveMode ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    _directoryFlags = QDir::NoDotAndDotDot | QDir::Files;
    if (hiddenMode) _directoryFlags |= QDir::Hidden;
}

void Finder::processFiles(std::vector<QString> &pathVec) {
    for (auto &path: pathVec) {
        QFileInfo fileInfo(path);
        if (!fileInfo.exists()) {
            emit throwError(path + " : " + "file doesn't exist");
            continue;
        }
        if (fileInfo.isDir()) {
            calcDirSize(path);
            continue;
        }
        if (fileInfo.isFile() && !fileInfo.isExecutable()) {
            _paths.push_back(fileInfo.path());
            _totalSize += fileInfo.size();
            _sizes[fileInfo.path()] = fileInfo.size();
        }
    }
    int size = static_cast<int>(_paths.size());
    int workersNum = std::min(THREADS_NUM, size);
    if (workersNum == 0) {
        emit throwError("No files to process");
        emit done();
        return;
    }
    _workerSize = size / workersNum;
    if (size % workersNum != 0) ++_workerSize;
    for (int i = 0; i < workersNum; ++i) {
        _workers.emplace_back(createWorker());
    }
}



void Finder::findSubString(QString string) {
    _processedSize = 0;
    emit find(string);
}

void Finder::calcDirSize(QString &path) {
    for (QDirIterator it(path, _directoryFlags, _iterationFlags); it.hasNext();) {
        it.next();
        if (it.fileInfo().isFile() && !it.fileInfo().isExecutable()) {
            _paths.push_back(it.filePath());
            _totalSize += it.fileInfo().size();
            _sizes[it.filePath()] = it.fileInfo().size();
        }
    }
}

Worker *Finder::createWorker() {
    std::vector<QString> files;
    for (int i = 0; i < _workerSize && !_paths.empty(); ++i) {
        files.push_back(_paths.back());
        _paths.pop_back();
    }
    Worker* worker = new Worker(files, _preprocessMode);
    QThread *thread = new QThread();
    worker->moveToThread(thread);

    // TODO : connection
    connect(this, &Finder::find, worker, &Worker::findSubString);
    connect(worker, &Worker::throwError, this, &Finder::catchError);
    connect(worker, &Worker::throwMatch, this, &Finder::catchMatch);
    connect(worker, &Worker::throwNoMatch, this, &Finder::catchNoMatch);

    connect(this, &Finder::cancel, thread, &QThread::requestInterruption);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    connect(thread, &QThread::started, worker, &Worker::processFiles);

    thread->start();
    return worker;
}


void Finder::canceled() {
    emit cancel();
}

void Finder::catchError(QString str) {
    emit throwError(str);
}

void Finder::catchMatch(QString fileName, std::vector<std::pair<int, int>> coor) {
    catchNoMatch(fileName);
    emit throwMatch(fileName, coor);
}

void Finder::catchNoMatch(QString fileName) {
    _processedSize += _sizes[fileName];
    int per = static_cast<int>(_processedSize * 100 / _totalSize);
    emit updateProgress(per);
    if (per == 100) {
        emit done();
    }
}


