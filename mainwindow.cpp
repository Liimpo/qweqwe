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
   this->testPtr = new testing(this, 10);
   testPtr->setWindowFlags(this->windowFlags() ^ Qt::FramelessWindowHint);
   testPtr->exec();
   this->hiScoreTime = this->testPtr->getTimeSinceStart();
   if (testPtr->getIsWin())
    scorePtr->newResult(1,this->hiScoreTime);
}

void MainWindow::on_actionMedium_clicked()
{
    this->testPtr = new testing(this, 20);
    testPtr->setWindowFlags(this->windowFlags() ^ Qt::FramelessWindowHint);

    //Gömmer mainrutan :^)
    this->hide();
    testPtr->exec();
    this->show();

    this->hiScoreTime = this->testPtr->getTimeSinceStart();
    if (testPtr->getIsWin())
     scorePtr->newResult(2,this->hiScoreTime);
}

void MainWindow::on_actionHard_clicked()
{
    this->testPtr = new testing(this, 30);
    testPtr->setWindowFlags(this->windowFlags() ^ Qt::FramelessWindowHint);

    //Gömmer mainrutan :^)
    this->hide();
    testPtr->exec();
    this->show();

    this->hiScoreTime = this->testPtr->getTimeSinceStart();
    if (testPtr->getIsWin())
     scorePtr->newResult(3,this->hiScoreTime);
}

void MainWindow::on_hiscoreButton_clicked()
{
    this->hide();
    scorePtr->exec();
    this->show();
}
