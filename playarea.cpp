#include "playarea.h"
#include "ui_playarea.h"

PlayArea::PlayArea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayArea)
{
    ui->setupUi(this);
}

PlayArea::~PlayArea()
{
    delete ui;
}
