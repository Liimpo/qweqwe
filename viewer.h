#ifndef VIEWER_H
#define VIEWER_H

#include <QGraphicsView>
#include <QSize>

class Viewer : public QGraphicsView
{
    Q_OBJECT

public:
    Viewer(QWidget *parent = 0);
    Viewer(QGraphicsScene *scene, QWidget *parent = 0);
    virtual ~Viewer();
};

#endif // VIEWER_H
