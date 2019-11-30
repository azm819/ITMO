#ifndef TRIGRAMMFINDER_H
#define TRIGRAMMFINDER_H

#include <QObject>

#include <thread>
#include <queue>
#include <QDirIterator>
#include <mutex>
#include <unordered_map>

#include "utils.h"
#include "worker.h"

const int THREADS_NUM = 8;

class Finder : public QObject {
    Q_OBJECT
public:
    Finder(bool hiddenMode, bool recursiveMode, bool preprocessMode);

    void processFiles(std::vector<QString>&);

    void findSubString(QString);


signals:
    void throwError(QString);
    void find(QString);
    void cancel();
    void throwMatch(QString, std::vector<std::pair<int, int>>);
    void updateProgress(int);
    void done();

public slots:
    void canceled();

private slots:
    void catchError(QString);
    void catchMatch(QString, std::vector<std::pair<int, int>>);
    void catchNoMatch(QString);

private:

    bool _preprocessMode;

    void calcDirSize(QString&);
    Worker* createWorker();

    std::mutex _sizeMutex;

    QFlags<QDirIterator::IteratorFlag> _iterationFlags;
    QFlags<QDir::Filter> _directoryFlags;

    std::vector<std::unique_ptr<Worker>> _workers;
    std::unordered_map<QString, qint64> _sizes;
    std::vector<QString> _paths;
    qint64 _totalSize;
    std::atomic<qint64> _processedSize;
    int _workerSize;
};

#endif // TRIGRAMMFINDER_H
