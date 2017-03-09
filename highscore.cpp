#include "highscore.h"
#include "ui_highscore.h"
#include <QDebug>

#define  TOP 10
#define NAMEPOS 0
#define DIFFPOS 1
#define TIMEPOS 2

#define ASD "-"

Highscore::Highscore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Highscore),
    mineSettings(0)
{
    ui->setupUi(this);
    //Vill att min toplista ska visa "top 10. skapar en constant TOP som är 10."
    ui->hiscoreTable->setRowCount(TOP);

    //Tabell med element
    for (int i = 0; i < ui->hiscoreTable->rowCount(); i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            QTableWidgetItem *tmpItem = new QTableWidgetItem();
            tmpItem->setText(ASD);
            ui->hiscoreTable->setItem(i,j,tmpItem);
        }

    }
}

Highscore::~Highscore()
{
    delete ui;
}

void Highscore::settingsHandler(QSettings * setting)
{
    this->mineSettings = setting;
}

bool Highscore::newResult(int diff,int time)
{
    bool success = false;
    int posInScore = -1;
    //Loop som kollar vart resultat ska placeras ut i hiscore.
    for (int i = TOP - 1; i >= 0; i--)
    {
        int tempDiff = 0;
        int tempTime = 0;
        if ( ui->hiscoreTable->item(i, DIFFPOS)->text() == ASD || ui->hiscoreTable->item(i, TIMEPOS)->text() == ASD)
        {
            posInScore = i;
        }
        //Ska alltid placera bästa resultatet längst upp, dvs svårighetsgrad 2 = högst.
        else
        {
        tempTime = ui->hiscoreTable->item(i, TIMEPOS)->text().toInt();
        tempDiff = ui->hiscoreTable->item(i, DIFFPOS)->text().toInt();
        }

        //Kollar om resultatet som ligger högst upp är slaget.
        if (diff > tempDiff || (diff == tempDiff && time < tempTime))
            posInScore = i;
    }

    //Om index som hittats är inom vår tabell.
    if (posInScore >= 0 && posInScore < ui->hiscoreTable->rowCount())
    {
        ui->hiscoreTable->insertRow(posInScore);
        //Då ska vi pilla på den raden och stoppa in våra värden.
        ui->hiscoreTable->setItem(posInScore, NAMEPOS, new QTableWidgetItem());
        ui->hiscoreTable->setItem(posInScore, DIFFPOS, new QTableWidgetItem());
        ui->hiscoreTable->setItem(posInScore, TIMEPOS, new QTableWidgetItem());

        //Slänger ut det sista scoret i resultatet.
        ui->hiscoreTable->removeRow(ui->hiscoreTable->rowCount() - 1);

        success = true;
        //Det här är en koll så att användaren matar in ett namn. Annars skrivs unknown in som vinnare.
        /*bool isOk;

        QString namePrep(QDir::home().dirName());

        //Om förberedelsen för att stoppa in ett namn är ok.
        if (namePrep.isEmpty() == false)
        {
            QChar firstChar = namePrep.at(0);

            if (firstChar.isLower() == true) namePrep[0] = firstChar.toUpper();
        }*/

        QString name = QInputDialog::getText(parentWidget(), tr("GAZORPAZORPFIELDSWEEPER"), tr("You're winner"), QLineEdit::Normal);

        //Sätt namn som unknown.
        if (name.isEmpty() == true)
            name = tr("NONAME");
        if (name == "-")
            name = tr("NONAME");

        //Tilldelar alla platser i hiscore.
        ui->hiscoreTable->item(posInScore, NAMEPOS)->setText(name);
        ui->hiscoreTable->item(posInScore, DIFFPOS)->setText(QString::number(diff));
        ui->hiscoreTable->item(posInScore, TIMEPOS)->setText(QString::number(time));

        //Visar tabellen.
        //this->show();
    }
    return success;
}

/*void Highscore::tableLoad()
{
    ui->hiscoreTable->setColumnWidth();
}*/

void Highscore::tableSave()
{
    mineSettings->setValue(QString("table/column") + QString::number(NAMEPOS), ui->hiscoreTable->columnWidth(NAMEPOS));
    mineSettings->setValue(QString("table/column") + QString::number(DIFFPOS), ui->hiscoreTable->columnWidth(DIFFPOS));
    mineSettings->setValue(QString("table/column") + QString::number(TIMEPOS), ui->hiscoreTable->columnWidth(TIMEPOS));

    for (int i = 0; i < ui->hiscoreTable->rowCount() && mineSettings != 0; i++)
    {
        mineSettings->setValue(QString("highscore/") + QString::number(i) + QString("name"), ui->hiscoreTable->item(i, NAMEPOS)->text());
        mineSettings->setValue(QString("highscore/") + QString::number(i) + QString("difficulty"), ui->hiscoreTable->item(i, DIFFPOS)->text());
        mineSettings->setValue(QString("highscore/") + QString::number(i) + QString("time"), ui->hiscoreTable->item(i, TIMEPOS)->text());
    }
}

void Highscore::on_pushButton_clicked()
{
    this->close();
}
