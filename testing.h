#ifndef TESTING_H
#define TESTING_H

#include <QMessageBox>
#include <QDialog>
#include <QStatusBar>
#include <QKeyEvent>
#include <QPushButton>
#include <QSignalMapper>
#include "QtMath"
#include <QTimer>
#include "sweepboard.h"
#include "b.h"

namespace Ui {
class testing;
}

class testing : public QDialog
{
    Q_OBJECT

public:
    explicit testing(QWidget *parent = 0, int gameMode = 10);
    void setNrOfMines(int mines);
    void setSizeOfBoard(int size);
    int getNrOfMines()const;
    int getSizeOfBoard()const;
    int getTimeSinceStart()const;
    virtual ~testing();

    void setIcon(b*, int row, int column);
    void winCase();
    void loseCase();
    void revealClose(int row, int column);
    bool getIsWin()const;
public slots:
    void refreshTime();
    void buttonIsPressed(QString);
    void otherButtonIsPressed(QString);

signals:
    void minesRemaining(int);

private:
    Ui::testing *ui;
    int timeSinceStart;
    int mineVal;
    int sizeOfBoard;
    bool isAWin;
    int mineIsFlagged;
    int nrOfFlags;
    int gameMode;
    int nrOfMines, mineGoal;
    QMessageBox *box;
    b *ptr;
    QTimer *timer;
    QSignalMapper *signalMapper, *signalMapper2;
    SweepBoard *game;
    int boardChecker[8][8];

private slots:
    void mineStatusText(int val);

protected:
    virtual void keyPressEvent(QKeyEvent * event);
};

#endif // TESTING_H
