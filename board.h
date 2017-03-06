#ifndef BOARD_H
#define BOARD_H

#include <QDialog>

namespace Ui {
class board;
}

class board : public QDialog
{
    Q_OBJECT

public:
    explicit board(QWidget *parent = 0);
    ~board();

private:
    Ui::board *ui;
};

#endif // BOARD_H
