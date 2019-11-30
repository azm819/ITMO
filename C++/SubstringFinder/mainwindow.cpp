#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>

#include <queue>
#include <unordered_set>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _requests(new QVBoxLayout())
    , _output(new QTextEdit)
    , _finder(nullptr) {
    ui->setupUi(this);
    _output->setReadOnly(true);
    ui->requestScrollArea->widget()->setLayout(_requests);
    clearRequests();

    _output->setPlaceholderText("Here will be the result");
    ui->resultScrollArea->setWidget(_output);

    init();
    ui->recursiveBox->setChecked(true);
    ui->substringLine->setPlaceholderText("Enter request");
}

MainWindow::~MainWindow() {
    clearRequests();
    delete _requests;
    delete _output;
    delete ui;
}

void MainWindow::init() {
    ui->addButton->setEnabled(true);
    ui->recursiveBox->setEnabled(true);
    ui->hiddenBox->setEnabled(true);
    ui->preprocessBox->setEnabled(true);
    ui->substringLine->setEnabled(true);

    ui->deleteButton->setEnabled(false);
    ui->cancelButton->setEnabled(false);
    ui->scanButton->setEnabled(false);
    ui->progressBar->hide();
}

void MainWindow::clearRequests() {
    while (_requests->count() > 0) {
        QLineEdit *line = qobject_cast<QLineEdit*>(_requests->itemAt(0)->widget());
        line->hide();
        delete line;
    }
}

void MainWindow::change() {
    if (!_changed) {
        _changed = true;
        for (int i = 0; i < _requests->count(); ++i) {
            _requests->itemAt(i)->widget()->setEnabled(true);
        }
    }

}

void MainWindow::on_substringLine_editingFinished() {
    ui->scanButton->setEnabled(ui->substringLine->text().isEmpty() ? false : true);
}

void MainWindow::customSlot() {}

void MainWindow::on_addButton_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory for Scanning", QString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (dir.size() == 0) return;
    change();
    QLineEdit *line = new QLineEdit;
    line->setPlaceholderText("Enter directory or file name");
    line->setMinimumHeight(25);
    line->setText(dir);
    _requests->addWidget(line);
    if (!ui->deleteButton->isEnabled()) ui->deleteButton->setEnabled(true);
}

void MainWindow::on_deleteButton_clicked() {
    change();
    int last = _requests->count() - 1;
    QLineEdit *line = qobject_cast<QLineEdit*>(_requests->itemAt(last)->widget());
    line->hide();
    delete line;
    if (last == 1) ui->deleteButton->setEnabled(false);
}

void MainWindow::on_recursiveBox_stateChanged(int arg) {
    change();
    _recursiveMode = arg ? true : false;
}

void MainWindow::on_hiddenBox_stateChanged(int arg) {
    change();
    _hiddenMode = arg ? true : false;
}

void MainWindow::on_preprocessBox_stateChanged(int arg) {
    change();
    _preprocessMode = arg ? true : false;
}

void MainWindow::on_scanButton_clicked() {
    _output->clear();
    QLineEdit *line;
    int last = _requests->count() - 1;
    while (_requests->count() > 1 && last >= 0) {
        line = qobject_cast<QLineEdit *>(_requests->itemAt(last)->widget());
        if (line->text().isEmpty()) {
            line->hide();
            delete line;
        }
        last--;
    }
    line = qobject_cast<QLineEdit *>(_requests->itemAt(0)->widget());
    if (line->text().isEmpty()) {
        QMessageBox::critical(this, "ошибка", "Поле запросов пусто");
        return;
    }
    ui->cancelButton->setEnabled(true);
    ui->substringLine->setEnabled(false);
    ui->scanButton->setEnabled(false);
    ui->addButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->recursiveBox->setEnabled(false);
    ui->hiddenBox->setEnabled(false);
    ui->preprocessBox->setEnabled(false);

    ui->progressBar->show();
    ui->progressBar->reset();

    std::vector<QString> vec;
    std::unordered_set<QString> set;
    for (int i = 0; i < _requests->count(); ++i) {
        line = qobject_cast<QLineEdit *>(_requests->itemAt(i)->widget());
        line->setEnabled(false);
        QString text = line->text();
        if (set.find(text) == set.end()) {
            set.insert(text);
            vec.push_back(text);
        }
    }
    set.clear();
    if (_changed) {
        _finder.reset(new Finder(_hiddenMode, _recursiveMode, _preprocessMode));
        connect(_finder.get(), &Finder::throwError, this, &MainWindow::catchError);
        connect(_finder.get(), &Finder::throwMatch, this, &MainWindow::processMatch);
        connect(_finder.get(), &Finder::updateProgress, this, &MainWindow::increase);
        connect(_finder.get(), &Finder::done, this, &MainWindow::finished);
        connect(ui->cancelButton, &QAbstractButton::clicked, _finder.get(), &Finder::canceled);

        _changed = false;
    }
    _finder->processFiles(vec);
    _finder->findSubString(ui->substringLine->text());
}

void MainWindow::catchError(QString str) {
    std::unique_lock<std::mutex> lock(_outputMutex);
    _output->insertHtml("<div><font color=\"red\">" + str + "</font></div>");
}

void MainWindow::processMatch(QString file, std::vector<std::pair<int, int>> coor) {
    std::unique_lock<std::mutex> lock(_outputMutex);
    for (auto &p: coor) {
        QString str = file + " :   " + QString::number(p.first) + ":" + QString::number(p.second);
        _output->append(str);
    }
}

void MainWindow::increase(int p) {
    std::unique_lock<std::mutex> lock(_progressBarMutex);
    ui->progressBar->setValue(p);
}

void MainWindow::finished() {
    init();
    QMessageBox::information(this, "INFO", "Scan completed");
}

void MainWindow::on_cancelButton_clicked() {
    init();
}
