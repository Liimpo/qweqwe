#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSize>
#include <QMap>
#include <QString>
#include <QList>
#include "minecounter.h"
#include "minefields.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QGraphicsView *parent = 0);
    virtual ~Scene();

    int getWidth() const;
    int getHeight() const;
    int getBombs() const;

public slots:
    void newGame(int, int);
    void newGame(int, int, int);
    void lockedField();
    void explosionActivated();

signals:
    void freeField(bool);
    void minesRemaining(int);
    void winCase();
    void explosions();
    void mineWarning();
    void fieldRevealed();
    void fieldFlagged();

private slots:
    void buildBoard();
    void positionFields();
    void forgeNeighbourFields();
    void putMinesInField();
    void deleteBoard();

private:
    int scale;
    int widthBoard;
    int heightBoard;
    int mineVal;
    QSize lastAdoptedSize;
    QMap<QString, Minefields*> listOfMines;
    QList <Minefields*> sharp, overallList;
    bool explosion;
    MineCounter *minecounter;
    QGraphicsView *viewer;
};

#endif // SCENE_H
