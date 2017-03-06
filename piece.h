#ifndef PIECE_H
#define PIECE_H
#include <QPushButton>
#include <QObject>
#include <QWidget>
#include <QMouseEvent>

class Piece : public QPushButton
{
    Q_OBJECT
public:
    Piece(QWidget *parent = 0);
signals:
    //void doubleClicked();

protected:
    //virtual void mouseDoubleClickEvent(QMouseEvent*);
};

#endif // PIECE_H
