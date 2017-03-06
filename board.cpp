#include "board.h"
#include "board.ui"

board::board(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::board)
{
    ui->setupUi(this);
}

board::~board()
{
    delete ui;
}
