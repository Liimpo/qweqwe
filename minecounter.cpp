#include "minecounter.h"

using namespace std;

MineCounter::MineCounter(QObject *parent)
    : QObject(parent), nrOfMines(0), nrOfFields(0)
{

}

MineCounter::~MineCounter()
{

}

int MineCounter::getMines() const
{
    return this->nrOfMines;
}

void MineCounter::setMineNumber(int mineVal)
{
    this->nrOfMines = mineVal;

    emit newMinePlace(this->nrOfMines);
}

void MineCounter::mineFieldAdder()
{
    this->nrOfFields++;

    emit newMinePlace(++this->nrOfMines);
}

void MineCounter::removeMines()
{
    emit newMinePlace(--this->nrOfMines);

    if(--this->nrOfFields == 0)
        emit allFieldsDelete();
}

void MineCounter::setFieldNumber(int fieldVal)
{
    this->nrOfFields = fieldVal;
}

void MineCounter::fieldAdder()
{
    ++this->nrOfFields;
}

void MineCounter::removeField()
{
    if (--this->nrOfFields == 0)
        emit allFieldsDelete();
}
