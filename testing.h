#ifndef TESTING_H
#define TESTING_H

#include <QMessageBox>
#include "minecounter.h"
#include <QDialog>
#include <QStatusBar>
#include <QKeyEvent>
#include <QPushButton>
#include <QSignalMapper>
#include "QtMath"
#include "sweepboard.h"
#include "b.h"

namespace Ui {
class testing;
}

class testing : public QDialog
{
    Q_OBJECT

public:
    explicit testing(QWidget *parent = 0, int mineNr = 0, int startSize = 0);
    void setNrOfMines(int mines);
    void setSizeOfBoard(int size);
    int getNrOfMines()const;
    int getSizeOfBoard()const;
    virtual ~testing();

    void setIcon(b*, int row, int column);
    void winCase();
public slots:
    void buttonIsPressed(QString);
    void otherButtonIsPressed(QString);

signals:
    void minesRemaining(int);

private:
    Ui::testing *ui;
    int mineVal;
    int mineIsFlagged;
    int nrOfFlags;
    int sizeOfBoard;
    int nrOfMines, mineGoal;
    QMessageBox *box;
    b *ptr;
    QSignalMapper *signalMapper, *signalMapper2;
    SweepBoard *game;
    int boardChecker[8][8];

private slots:
    void mineStatusText(int val);

protected:
    virtual void keyPressEvent(QKeyEvent * event);
};

#endif // TESTING_H
