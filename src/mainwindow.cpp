#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include<QTextStream>
#include<QLineEdit>
#include<QTextEdit>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void work();

void MainWindow::on_getFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"open assembly file","c://","Text files (*.txt);");
    //code to open the c++ file and doing everything
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"title","error in opening file");
    }
    else{
    readAllLine = QTextStream(&file).readAll().toStdString();
    work();
    }
}




