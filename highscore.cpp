#include "highscore.h"
#include "ui_highscore.h"

#define  TOP 10
Highscore::Highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Highscore)
{
    ui->setupUi(this);
    //Vill att min toplista ska visa "top 10. skapar en constant TOP som är 10."
    ui->hiscoreTable->setRowCount(TOP);
}

Highscore::~Highscore()
{
    delete ui;
}

void Highscore::on_pushButton_clicked()
{
    this->close();
}
