#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QThreadPool>
#include <QFutureWatcher>
#include <QDir>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class FileSearcher;


class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:


    void onBrowseClicked();
    void onSearchClicked();
    void onClearClicked();
    void displayResults(const QVector<QFileInfo>& results);


private:
    void setupConnections();
    void resetUI();
    Ui::MainWindow *ui;
    QThreadPool m_threadPool;
    FileSearcher *m_searcher = nullptr;
    QFutureWatcher<void> m_watcher;


};


#endif // MAINWINDOW_H




