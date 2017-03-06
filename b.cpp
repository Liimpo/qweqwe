#include "b.h"

b::b(QWidget *parent)
    : QPushButton(parent)
{
    setStyleSheet("background-color: black");
}

b::~b()
{

}

void b::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
        emit rightClicked();
    else if(e->button()==Qt::LeftButton)
        emit leftClicked();
}
