#ifndef TRIGRAMMWorker_H
#define TRIGRAMMWorker_H

#include <QObject>
#include <QWaitCondition>
#include <QMutex>
#include <QFile>

#include <set>
#include <functional>
#include <memory>

#include "utils.h"


class Worker : public QObject {
    Q_OBJECT
public:
    Worker(std::vector<QString>&, bool);

    void findSubString(QString);

signals:
    void throwError(QString);
    void throwMatch(QString, std::vector<std::pair<int, int>>);
    void throwNoMatch(QString);

public slots:
    void processFiles();
    void pause();
    void resume();

private:
    struct TrigrammHolder {
        TrigrammHolder(QString&);

        QString _path;
        std::set<uint64_t> _trigramms;
    };

    void defaultSearching(QString&);

    std::vector<TrigrammHolder> _trigrammHolders;
    std::unique_ptr<BMH_SEARCHER> _searcher;

    bool _preprocess;
};

#endif // TRIGRAMMWorker_H
