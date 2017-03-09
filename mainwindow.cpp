#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMoveEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mineSettings = new QSettings("Linus Malmfelt", "Gazorpazorpfieldsweeper", this);
    this->scorePtr = new Highscore();
    scorePtr->settingsHandler(this->mineSettings);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEasy_clicked()
{
   this->testPtr = new testing(this, 1, 64);
   //testPtr->setFixedSize(300,300);
   testPtr->setWindowFlags(this->windowFlags() ^ Qt::FramelessWindowHint);
   testPtr->exec();
   this->hiScoreTime = this->testPtr->getTimeSinceStart();
   scorePtr->newResult(1,this->hiScoreTime);
}

void MainWindow::on_hiscoreButton_clicked()
{
    scorePtr->exec();
}
