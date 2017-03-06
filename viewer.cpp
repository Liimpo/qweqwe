#include "viewer.h"
#include <QResizeEvent>
#include <QScrollBar>
#include "Scene.h"

using namespace std;

Viewer::Viewer(QWidget *parent) : QGraphicsView(parent)
{
        setBackgroundBrush(Qt::green);
}

Viewer::Viewer(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{
    setBackgroundBrush(Qt::green);
}

Viewer::~Viewer()
{

}
