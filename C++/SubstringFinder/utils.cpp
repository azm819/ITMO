#include "utils.h"

#include <QFile>
#include <QTextStream>
#include <QThread>

std::vector<std::pair<int, int>> searchInFile(QString &path, BMH_SEARCHER *searcher) {
    QFile file(path);
    file.open(QFile::ReadOnly);
    std::vector<std::pair<int, int>> res{};
    QString line;
    QTextStream stream(&file);
    line = stream.readLine(BUFFER_SIZE);
    int lineNum = 1;
    while (line.size() > 0) {
        if (QThread::currentThread()->isInterruptionRequested()) {
            break;
        }
        int index = 0;
        auto it = line.begin();
        while ((it = std::search(it, line.end(), *searcher)) != line.end()) {
            if (QThread::currentThread()->isInterruptionRequested()) {
                break;
            }
            index += it++ - line.begin();
            res.emplace_back(lineNum, index);
        }
        lineNum++;
        line = stream.readLine(BUFFER_SIZE);
    }
    return res;
}

//std::initializer_list<uint64_t> getTrigramms(QString &line) {
//    uint64_t trigramm = (((uint64_t) line[0].unicode()) << SMALL_SHIFT) + (((uint64_t) line[1].unicode()) << BIG_SHIFT);
//    std::initializer_list<uint64_t> res;
//    for (int i = 2; i < line.size(); ++i) {
//        if (QThread::currentThread()->isInterruptionRequested()) {
//            break;
//        }
//        trigramm = (trigramm >> SMALL_SHIFT) + (((uint64_t) line[i].unicode()) << BIG_SHIFT);
////        res
//    }
//    return res;
//}
