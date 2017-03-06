#ifndef MINECOUNTER_H
#define MINECOUNTER_H

#include <QObject>

class MineCounter : public QObject
{
    Q_OBJECT

public:
    MineCounter(QObject *parent = 0);
    virtual ~MineCounter();

    int getMines() const;
    int getFields() const;

public slots:
    void setMineNumber(int mineVal);
    void mineFieldAdder();
    void removeMines();
    void setFieldNumber(int fieldVal);
    void fieldAdder();
    void removeField();

signals:
    void newMinePlace(int);
    void allFieldsDelete();

private:
    int nrOfMines, nrOfFields;
};

#endif // MINECOUNTER_H
