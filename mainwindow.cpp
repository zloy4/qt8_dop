#include "mainwindow.h"
 #include "ui_mainwindow.h"
 #include <QFileDialog>
 #include <QMessageBox>
 #include <QDateTime>
 #include <QTime>
#include "filesearcher.h"

 MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setupConnections();
    resetUI();
 }

 MainWindow::~MainWindow() {
    delete ui;
 }

 void MainWindow::setupConnections() {
    connect(ui->browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
 }

 void MainWindow::resetUI() {
    ui->resultList->clear();
     ui->progressBar->setValue(0);
 }

 void MainWindow::onBrowseClicked() {
    QString directory = QFileDialog::getExistingDirectory(this, tr("Выберите директорию"));
    if (!directory.isEmpty()) {
         ui->directoryEdit->setText(directory);
    }
 }

 void MainWindow::onSearchClicked() {
    QString rootDir = ui->directoryEdit->text();
    if (rootDir.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не выбрана директория."));
        return;
    }

    FileSearcher::SearchCriteria criteria;
    criteria.extension = ui->extensionBox->currentText();
        criteria.regex = QRegularExpression(ui->lineEdit_regex->text());

    if (ui->minSizeSpin->value() > 0)
        criteria.minSize = ui->minSizeSpin->value() * 1024;

    if (ui->maxSizeSpin->value() > 0)
        criteria.maxSize = ui->maxSizeSpin->value() * 1024;

    if (ui->dateEdit_from->date().isValid())
        criteria.dateFrom = QDateTime(ui->dateEdit_from->date(), QTime(0, 0));

    if (ui->dateEdit_to->date().isValid())
        criteria.dateTo = QDateTime(ui->dateEdit_to->date(), QTime(23, 59, 59));

    ui->resultList->clear();

    QVector<QFileInfo> results = m_searcher->search(rootDir, criteria);
    displayResults(results);
 }

 void MainWindow::onClearClicked() {
    resetUI();
 }

 void MainWindow::displayResults(const QVector<QFileInfo>& results) {
    for (const QFileInfo &info : results) {
         ui->resultList->addItem(info.absoluteFilePath());
    }

         ui->progressBar->setValue(100);
 }



