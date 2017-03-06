#include "Scene.h"
#include "Minefields.h"
#include "Minecounter.h"
#include "scene.h"
#include <QStringList>
#include <QDateTime>
#define SPLITTER ","

using namespace std;

Scene::Scene(QGraphicsView *parent)
    : QGraphicsScene(parent), widthBoard(0), heightBoard(0), mineVal(0), explosion(false)
{
    minecounter = new MineCounter(this);
    minecounter->setObjectName("minecounter");

    connect(minecounter, SIGNAL(newMinePlace(int)), this, SIGNAL(minesRemaining(int)));
    connect(minecounter, SIGNAL(allFieldsDelete()), this, SLOT(lockedField()));
}

Scene::~Scene()
{

}

void Scene::newGame(int tempWidth, int tempHeight)
{
    deleteBoard();

    explosion = false;

    this->widthBoard = tempWidth;
    this->heightBoard = tempHeight;

    this->mineVal = this->widthBoard * this->heightBoard / 5;

    buildBoard();

    forgeNeighbourFields();

    putMinesInField();

    positionFields();

    emit freeField(true);
}

void Scene::buildBoard()
{
    int minesToPlace = (this->widthBoard * this->heightBoard) - overallList.size();
    setSceneRect(0,0, (this->widthBoard * SIZE), (this->heightBoard * SIZE));

    //Putting mines on the board
    if (minesToPlace > 0)
    {
        for(int i = 0; i < minesToPlace; i++)
        {
            Minefields *tempMine = new Minefields(this);
            tempMine->mineCounterRegister(minecounter);
            tempMine->setAcceptHoverEvents(true);

            connect(tempMine, SIGNAL(explosions()), this, SLTO(explosionActivated()));

            connect(this, SIGNAL(freeField(bool)), tempMine, SLOT(setEnabled(bool)));

            connect(tempMine, SIGNAL(mineWarning()), this, SIGNAL(mineWarning()));

            connect(tempMine, SIGNAL(fieldRevealed()), this, SIGNAL(fieldRevealed()));

            connect(tempMine, SIGNAL(fieldFlagged()), this, SIGNAL(fieldFlagged()));

            overallList.append(tempMine);
        }
    }

    else if (minesToPlace < 0 && overallList.size() > (15*15))
    {
        for (int i = 0; i > minesToPlace; i --)
        {
            delete overallList.takeLast();
        }
    }

    int commonIndex = 0;

    for (int row = 0; commonIndex < overallList.size() && row < this->heightBoard; row++)
    {
        for (int column = 0; commonIndex < overallList.size() && column < this->widthBoard; column++, commonIndex++)
        {
            Minefields *tempMine = overallList.at(commonIndex);

            tempMine->setObjectName(QString::number(column) + SPLITTER + QString::number(row));

            addItem(tempMine);

            listOfMines.insert(tempMine->objectName(), tempMine);
        }
    }
}

void Scene::positionFields()
{
    for (int i = 0; i < this->heightBoard; i++)
    {
        for (int j = 0; j < this->widthBoard; j++)
        {
            listOfMines.value(QString::number(j) + SPLITTER + QString::number(i))->setPos(j * SIZE, i * SIZE);
        }
    }
}

void Scene::forgeNeighbourFields()
{
    for (int row = 0; row < this->heightBoard; row++)
    {
        for (int column; column < this->widthBoard; column++)
        {
            //nw
            if (listOfMines.contains(QString::number(column - 1) + SPLITTER + QString::number(row - 1)) == true) listOfMines.value(QString::number(column) + SPLITTER + QString::number(row))->createNeighbourFields(listOfMines.value(QString::number(column - 1) + SPLITTER + QString::number(row - 1)));

            // n
            if (listOfMines.contains(QString::number(column) + SPLITTER + QString::number(row - 1)) == true) listOfMines.value(QString::number(column) + SPLITTER + QString::number(row))->createNeighbourFields(listOfMines.value(QString::number(column) + SPLITTER + QString::number(row - 1)));

            // ne
            if (listOfMines.contains(QString::number(column + 1) + SPLITTER + QString::number(row - 1)) == true) listOfMines.value(QString::number(column) + SPLITTER + QString::number(row))->createNeighbourFields(listOfMines.value(QString::number(column + 1) + SPLITTER + QString::number(row - 1)));

             // w
             if (listOfMines.contains(QString::number(column - 1) + SPLITTER + QString::number(row)) == true) listOfMines.value(QString::number(column) + SPLITTER + QString::number(row))->createNeighbourFields(listOfMines.value(QString::number(column - 1) + SPLITTER + QString::number(row)));

             // e
             if (listOfMines.contains(QString::number(column + 1) + SPLITTER + QString::number(row)) == true) listOfMines.value(QString::number(column) + SPLITTER + QString::number(row))->createNeighbourFields(listOfMines.value(QString::number(column + 1) + SPLITTER + QString::number(row)));

             // sw
             if (listOfMines.contains(QString::number(column - 1) + SPLITTER + QString::number(row + 1)) == true) listOfMines.value(QString::number(column) + SPLITTER + QString::number(row))->createNeighbourFields(listOfMines.value(QString::number(column - 1) + SPLITTER + QString::number(row + 1)));

             // s
             if (listOfMines.contains(QString::number(column) + SPLITTER + QString::number(row + 1)) == true) listOfMines.value(QString::number(column) + SPLITTER + QString::number(row))->createNeighbourFields(listOfMines.value(QString::number(column) + SPLITTER + QString::number(row + 1)));

             // se
             if (listOfMines.contains(QString::number(column + 1) + SPLITTER + QString::number(row + 1)) == true) listOfMines.value(QString::number(column) + SPLITTER + QString::number(row))->createNeighbourFields(listOfMines.value(QString::number(column + 1) + SPLITTER + QString::number(row + 1)));
        }
    }
}

void Scene::putMinesInField()
{
    QList<Minefields*> hidden(listOfMines.values());
    qsrand(time(NULL));

    while (hidden.size() > 1 && sharp.size() < this->mineVal)
    {
        Minefields *row = hidden.at(qrand()% hidden.size()-1);

        row->plantAMine();

        hidden.removeAll(row);

        sharp.append(row);
    }

    if (sharp.size() < this->mineVal && hidden.isEmpty() == false)
    {
        Minefields *row = hidden.first();

        row->plantAMine();

        hidden.removeAll(row);

        sharp.append(row);
    }

    minecounter->setMineNumber(sharp.size());
    minecounter->setFieldNumber(this->widthBoard * this->heightBoard);
}

void Scene::explosionActivated()
{
    if (explosion == false)
    {
        explosion = true;

        emit freeField(false);

        emit explosions;

        for (int i = 0; i < sharp.size(); i++)
            sharp.at(i)->coverField();
    }
}

void Scene::deleteBoard()
{
    scale = 0;

    emit freeField(false);

    QStringList keys(listOfMines.keys());

    for (int i = 0; i < keys.size(); i++)
    {
        removeItem(listOfMines.value(keys.at(i)));

        listOfMines.value(keys.at(i))->reset();
    }

    sharp.clear();
    listOfMines.clear();
}

void Scene::lockedField()
{
    emit freeField(false);

    if (explosion == false)
        emit winCase();
}

void Scene::newGame(int tempWidth, int tempHeight, int temptBombs)
{
    deleteBoard();

    explosion = false;

    this->widthBoard = tempWidth;
    this->heightBoard = tempHeight;

    this->mineVal = temptBombs;

    buildBoard();

    forgeNeighbourFields();

    putMinesInField();

    positionFields();

    emit freeField(true);
}

int Scene::getWidth() const
{
    return this->widthBoard;
}

int Scene::getHeight() const
{
    return this->heightBoard;
}

int Scene::getBombs() const
{
    return this->mineVal;
}
