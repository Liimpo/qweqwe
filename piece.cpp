#include "piece.h"
#include <QDebug>

Piece::Piece(QWidget *parent) :QPushButton(parent)
{
    this->setText("testing123");
}

/*virtual void Piece::mouseDoubleClickEvent(QMouseEvent *)
{
    //emit rightButtonClicked();
    ///Right click?
    if ( event->button() == Qt::RightButton)
    {
        emit rightButtonClicked();
    }

    //left click
    QPushButton::mousePressEvent(event);
}

void Piece::rightButtonClicked()
{
    QDebug() << "is Right.";
}
*/
