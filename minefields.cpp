#include "minefields.h"
#include <QPainter>
#include <QRect>
#include <QRectF>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>

using namespace std;

Minefields::Minefields(QObject *oparent, QGraphicsItem *gparent)
    //:QObject(oparent), QGraphicsItem(gparent), fieldVal(0), revealed(false), isFlagged(false), isEnabled(false), minecounter(0)
{

}

Minefields::~Minefields()
{

}

void Minefields::paint(QPainter* painter, QWidget*)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if (revealed == false)
    {
        QPixmap pixmap(":/plumbus.png");
        painter->drawPixmap(0,0,40,40, pixmap);

        if (isFlagged == true)
        {
            QPixmap pixmap2(":/flag.png");
            painter->drawPixmap(0,0,40,40,pixmap2);
        }
    }

    else
    {
        if (fieldVal > 0 && fieldVal <= 8)
        {
            QPixmap nrs(":/Drawing.jpeg");
            QPixmap nrs2(":/two.jpeg");
            QPixmap nrs3(":/three.jpeg");
            QPixmap nrs4(":/four.jpeg");
            switch (fieldVal)
            {
            case 1:
                //QPixmap nrs(":/Drawing.jpeg");
                painter->drawPixmap(0,0,40,40,nrs);
                break;
            case 2:
                //QPixmap nrs2(":/two.jpeg");
                painter->drawPixmap(0,0,40,40,nrs2);
                break;
            case 3:
                //QPixmap nrs3(":/three.jpeg");
                painter->drawPixmap(0,0,40,40,nrs3);
                break;
            case 4:
                //QPixmap nrs4(":/four.jpeg");
                painter->drawPixmap(0,0,40,40,nrs4);
                break;
            default:
                painter->drawPixmap(0,0,40,40,nrs4);
                break;
            }
        }

        else if (fieldVal == -1)
        {
            QPixmap bomber(":/Gazorpazorpfield_Bitch.png");
            painter->drawPixmap(0,0,40,40, bomber);
        }
    }

}

QRectF Minefields::boundingRect() const
{
    return QRect(QPoint(0,0), QSize(SIZE, SIZE));
}

void Minefields::createNeighbourFields(Minefields * tempNeighbor)
{
    neighbors.append(tempNeighbor);

    connect(tempNeighbor, SIGNAL(mineExists()), this, SLOT(neighbourIsAMine()));

    connect(tempNeighbor, SIGNAL(fieldIsRevealed(char)), this, SLOT(coverField(char)));
}

void Minefields::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (isEnabled == true && event->pos().x() > SAFETYSECTION && event->pos().y() > SAFETYSECTION)
    {
        QGraphicsItem::mousePressEvent(event);

        if (event->button() == Qt::LeftButton && revealed == false)
            coverField();

        else if (event->button() == Qt::RightButton && revealed == false)
        {
            if (isFlagged == false)
            {
                if (minecounter->getMines() > 0)
                    setAFlag();
            }
            else
                removeAFlag();
        }
    }
}

void Minefields::plantAMine()
{
    fieldVal = -1;

    update();

    emit mineExists();
}

bool Minefields::mineIsPressed() const
{
    bool pressed = false;

    if (fieldVal == -1)
        pressed = true;

    return pressed;
}

void Minefields::neighbourIsAMine()
{
    if (fieldVal != -1)
    {
        fieldVal++;
        update();
    }
}

void Minefields::coverField(char val)
{
    if (revealed == false && isFlagged == false)
    {
        if (val == 0 && fieldVal != -1)
            coverField();
    }
}

void Minefields::coverField()
{
    if ((revealed == false && isFlagged == false) || isEnabled == false)
    {
        revealed = true;
        update();

        emit fieldRevealed();

        if (fieldVal == -1)
            emit explosions();

        emit fieldIsRevealed(fieldVal);

        if (isEnabled == true)
            minecounter->removeField();
    }
}

void Minefields::setAFlag()
{
    if (isFlagged == false)
    {
        isFlagged = true;

        update();

        emit fieldFlagged();

        minecounter->removeMines();
    }
}

void Minefields::removeAFlag()
{
    if (isFlagged == true)
    {
        isFlagged = false;

        update();

        minecounter->mineFieldAdder();
    }
}

void Minefields::setEnabled(bool val)
{
    isEnabled = val;
}

void Minefields::reset()
{
    for (int i = 0; i < neighbors.size(); i++)
    {
        disconnect(neighbors.at(i), SIGNAL(mineExists()), this, SLOT(neighbourIsAMine()));
        disconnect(neighbors.at(i), SIGNAL(fieldIsRevealed(char)), this, SLOT(coverField(char)));
    }

    fieldVal = 0;
    revealed = isFlagged = isEnabled = false;
    neighbors.clear();
}

void Minefields::mineCounterRegister(MineCounter * object)
{
    minecounter = object;
}

void Minefields::hoverEnterEvent(QGraphicsSceneHoverEvent * event)
{
    QGraphicsItem::hoverEnterEvent(event);
    if (fieldVal == -1 && isFlagged == false)
        emit mineWarning();
}

void Minefields::hoverLeaveEvent(QGraphicsSceneHoverEvent * event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}
