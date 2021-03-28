#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_getFile_clicked();

public:
    Ui::MainWindow *ui;
    std::string readAllLine;
    bool run= false;
private slots:
    void on_nextStep_clicked();
    void on_runAll_clicked();
};
#endif // MAINWINDOW_H
