#ifndef PLAYAREA_H
#define PLAYAREA_H

#include <QDialog>

namespace Ui {
class PlayArea;
}

class PlayArea : public QDialog
{
    Q_OBJECT

public:
    explicit PlayArea(QWidget *parent = 0);
    ~PlayArea();

private:
    Ui::PlayArea *ui;
};

#endif // PLAYAREA_H
