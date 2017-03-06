#ifndef MINEFIELDS_H
#define MINEFIELDS_H


#include <QGraphicsItem>
#include <QObject>
#include <QSize>
#include <QList>
#include "minecounter.h"

#define SIZE 40
#define SAFETYSECTION 2


class Minefields : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Minefields(QObject *oparent, QGraphicsItem *gparent);
    virtual ~Minefields();

    bool mineIsPressed() const;
    void mineCounterRegister(MineCounter*);

public slots:
    void createNeighbourFields(Minefields*);
    void plantAMine();
    void neighbourIsAMine();
    void coverField(char);
    void coverField();
    void setAFlag();
    void removeAFlag();
    void setEnabled(bool);
    void reset();

signals:
    void mineExists();
    void fieldIsRevealed(char);
    void explosions();
    void mineWarning();
    void fieldRevealed();
    void fieldFlagged();

private:
    char fieldVal;
    bool revealed;
    bool isFlagged;
    bool isEnabled;
    QList<Minefields*> neighbors;
    MineCounter *minecounter;

    virtual void paint(QPainter*, QWidget*);
    virtual QRectF boundingRect() const;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*);
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent*);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent*);
};

#endif
