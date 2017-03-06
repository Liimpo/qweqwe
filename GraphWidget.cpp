#include "GraphWidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    //QPixmap pix1(":/four.jpeg");
   // QPixmap pix2(":/three.jpeg");
    //setBackgroundBrush(Qt::green);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    //setScene(scene);
    //setRenderHint(Qpainter::Antialiasing);
   // setMinimumSize(400,400);
    //setWindowTitle(tr("TEST"));

    //scene->addItem(pix1);
    //scene->addItem(pix2);
}
