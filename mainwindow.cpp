#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMoveEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEasy_clicked()
{
   this->testPtr = new testing(this, 9, 64);
   //testPtr->setFixedSize(300,300);
   testPtr->setWindowFlags(this->windowFlags() ^ Qt::FramelessWindowHint);
   testPtr->exec();
}
