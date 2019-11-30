#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>

#include "finder.h"
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_substringLine_editingFinished();
    void customSlot();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_recursiveBox_stateChanged(int arg1);
    void on_hiddenBox_stateChanged(int arg1);
    void on_preprocessBox_stateChanged(int arg1);
    void on_scanButton_clicked();
    void catchError(QString);
    void processMatch(QString, std::vector<std::pair<int, int>>);
    void increase(int);
    void finished();
    void on_cancelButton_clicked();

private:
    void init();
    void clearRequests();
    void change();

    Ui::MainWindow *ui;

    std::mutex _outputMutex;
    std::mutex _progressBarMutex;

    QVBoxLayout *_requests;
    QTextEdit *_output;

    bool _recursiveMode = true;
    bool _hiddenMode = false;
    bool _preprocessMode = false;

    bool _changed = true;

    std::unique_ptr<Finder> _finder;
};
#endif // MAINWINDOW_H
