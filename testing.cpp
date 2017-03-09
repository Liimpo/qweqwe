#include "testing.h"
#include "ui_testing.h"
#include "QDebug"
#include "QTextEdit"
#include "QWidget"
#include "QGridLayout"
#include <QString>
#include <QTimer>

#define EASY 10
#define MEDIUM 20
#define HARD 30

testing::testing(QWidget *parent, int gameMode) :
    QDialog(parent),
    ui(new Ui::testing)
{
    this->timeSinceStart = 0;
    this->nrOfFlags = 0;
    this->isAWin = false;
    this->gameMode = gameMode;
    //If this reaches nrOfMines u win.
    this->mineGoal = 0;
    //Sätter upp standardinställningar
    ui->setupUi(this);

    //Layout designs
    ui->mineBoard->setSpacing(0);
    ui->mineBoard->setHorizontalSpacing(0);
    //Här kommer gametimern som ska fixa med hiscore
    ui->gameTimer->setDigitCount(3);
    this->timer = new QTimer(this);

    connect(this->timer, SIGNAL(timeout()), this, SLOT(refreshTime()));
    this->timer->start(1000);

    //Objekternas platser på brädet mha Signalmapper
    signalMapper = new QSignalMapper(this);
    signalMapper2 = new QSignalMapper(this);

    if(this->gameMode == EASY)
    {
        this->game = new SweepBoard(4, 5); //4 är storleken.
        this->nrOfMines = 5;
        ui->flagCount->display(this->nrOfMines - this->nrOfFlags);

        //Behöver ytterliggare en multi-dim array som håller koll på om knappar är använda
        //Eller om en flagga är uppsatt.
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
                boardChecker[i][j] = 0;
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                ptr = new b(this);
                ptr->setAttribute(Qt::WA_LayoutUsesWidgetRect);
                ptr->setMaximumHeight(40);
                ptr->setMaximumWidth(40);
                ptr->setIcon(QIcon(":/plumbus.png"));
                ptr->setIconSize (QSize(40,40));

                ui->mineBoard->addWidget(ptr,i,j);
                //Skriver koordinaterna för knapparna och mappar signalmapper
                QString coordinates = QString::number(i)+","+QString::number(j);
                //Setting the coordinates.
                //Gör att varje knapp blir left och högerklickbar mha signalmapper.
                signalMapper->setMapping(ptr, coordinates);
                signalMapper2->setMapping(ptr, coordinates);
                connect(ptr, SIGNAL(leftClicked()), signalMapper, SLOT(map()));
                connect(ptr, SIGNAL(rightClicked()), signalMapper2, SLOT(map()));
            }
        }

    }
    else if (this->gameMode == MEDIUM)
    {
        this->game = new SweepBoard(6, 7); //6 är storleken.
        this->nrOfMines = 7;
        ui->flagCount->display(this->nrOfMines - this->nrOfFlags);

        for(int i = 0; i < 6; i++)
        {
            for(int j = 0; j < 6; j++)
                boardChecker[i][j] = 0;
        }

        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                ptr = new b(this);
                ptr->setAttribute(Qt::WA_LayoutUsesWidgetRect);
                ptr->setMaximumHeight(40);
                ptr->setMaximumWidth(40);
                ptr->setIcon(QIcon(":/plumbus.png"));
                ptr->setIconSize (QSize(40,40));

                ui->mineBoard->addWidget(ptr,i,j);
                //Skriver koordinaterna för knapparna och mappar signalmapper
                QString coordinates = QString::number(i)+","+QString::number(j);
                //Setting the coordinates.
                //Gör att varje knapp blir left och högerklickbar mha signalmapper.
                signalMapper->setMapping(ptr, coordinates);
                signalMapper2->setMapping(ptr, coordinates);
                connect(ptr, SIGNAL(leftClicked()), signalMapper, SLOT(map()));
                connect(ptr, SIGNAL(rightClicked()), signalMapper2, SLOT(map()));
            }
        }
    }
    else if (gameMode == HARD)
    {
        this->game = new SweepBoard(8, 16); //6 är storleken.

        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
                boardChecker[i][j] = 0;
        }

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                ptr = new b(this);
                ptr->setAttribute(Qt::WA_LayoutUsesWidgetRect);
                ptr->setMaximumHeight(40);
                ptr->setMaximumWidth(40);
                ptr->setIcon(QIcon(":/plumbus.png"));
                ptr->setIconSize (QSize(40,40));

                ui->mineBoard->addWidget(ptr,i,j);
                //Skriver koordinaterna för knapparna och mappar signalmapper
                QString coordinates = QString::number(i)+","+QString::number(j);
                //Setting the coordinates.
                //Gör att varje knapp blir left och högerklickbar mha signalmapper.
                signalMapper->setMapping(ptr, coordinates);
                signalMapper2->setMapping(ptr, coordinates);
                connect(ptr, SIGNAL(leftClicked()), signalMapper, SLOT(map()));
                connect(ptr, SIGNAL(rightClicked()), signalMapper2, SLOT(map()));
            }
        }
    }

    //Objekternas platser på brädet mha Signalmapper
    //signalMapper = new QSignalMapper(this);
    //signalMapper2 = new QSignalMapper(this);

    //nytt bord.
    //this->game = new SweepBoard(64, 11);
    //int cnt = 0;
    /*
    for (int i = 0; i < (sqrt((double)this->sizeOfBoard)); i++)
    {
        for (int j = 0; j < (sqrt((double)this->sizeOfBoard)); j++)
        {
            ptr = new b(this);
            ptr->setAttribute(Qt::WA_LayoutUsesWidgetRect);
            ptr->setMaximumHeight(40);
            ptr->setMaximumWidth(40);
            ptr->setIcon(QIcon(":/plumbus.png"));
            ptr->setIconSize (QSize(40,40));

            ui->mineBoard->addWidget(ptr,i,j);
            //Skriver koordinaterna för knapparna och mappar signalmapper
            QString coordinates = QString::number(i)+","+QString::number(j);
            //Setting the coordinates.
            //Gör att varje knapp blir left och högerklickbar mha signalmapper.
            signalMapper->setMapping(ptr, coordinates);
            signalMapper2->setMapping(ptr, coordinates);
            connect(ptr, SIGNAL(leftClicked()), signalMapper, SLOT(map()));
            connect(ptr, SIGNAL(rightClicked()), signalMapper2, SLOT(map()));
        }
    }*/
    this->setWindowTitle("SWOOPINGSWEEP");
    //Connectar koordintaerna från knapparna och beroende om det är vänster eller högerklick
    //Kommer olika saker att ske på de givna koordintarerna (dvs där knapparna är)
    connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(buttonIsPressed(QString)));
    connect(signalMapper2, SIGNAL(mapped(QString)), this, SLOT(otherButtonIsPressed(QString)));
}

testing::~testing()
{
    delete ui;
}

void testing::mineStatusText(int val)
{
    qDebug() << "fek" << &endl;
    //mineStatusLabel->setText(QString::number(val) + tr(" mines left"));
}

void testing::setNrOfMines(int mines)
{
    this->nrOfMines = mines;
}

void testing::setSizeOfBoard(int size)
{
    this->sizeOfBoard = size;
}

int testing::getNrOfMines()const
{
    return this->nrOfMines;
}

int testing::getSizeOfBoard()const
{
    return this->sizeOfBoard;
}

int testing::getTimeSinceStart()const
{
    return this->timeSinceStart;
}
bool testing::getIsWin()const
{
    return this->isAWin;
}
void testing::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        qDebug() << "Key pressed";
        this->box = new QMessageBox(this);
        box->setText("Do you want to Exit?");
        box->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int choice = box->exec();

        switch (choice)
        {
            case QMessageBox::No:
                qDebug() << "Returning..";
            break;
            case QMessageBox::Yes:
                this->close();
            break;
            default:
            //This will never occur
            break;
        }
    }
}

void testing::buttonIsPressed(QString coordinates)
{
    //skapar en knapp b buttonpressed och tar koordinaterna från platsen som signalmapper i konstruktorn har.
    //qobject castar för att jag ska få rätt knapp och kunna ändra på den som jag vill
    //Stoppar sedan in koordinaterna som en sträng i en lista. Listan ser ut: ["row,column"]
    b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(coordinates));
    QStringList results = coordinates.split(",");
    //Efter split blir listan ["row", "column"]. Sen ger jag mitt lokala row här plats 1 i listan och
    //column plats 2 i listan.
    int row = results.at(0).toInt();
    int column = results.at(1).toInt();

    //Om en knapp är flat ska den inte gå att trycka på. Inte heller om det är en flagga!
    if (!buttonPressed->isFlat() && boardChecker[row][column] != FLAG)
    {
        if (boardChecker[row][column] != FLAG)
            setIcon(buttonPressed, row, column);

        if (game->isAMine(row, column) && boardChecker[row][column] != FLAG)
            this->loseCase();

        //Om det är en tom ruta ska närliggande rutor visa sig. Eftersom det inte finns en mina jämte.
        if (game->getVal(row, column) == 0)
            this->revealClose(row, column);

        else if (!buttonPressed->isFlat() && boardChecker[row][column] != FLAG)
            buttonPressed->setFlat(true);
    }

}

void testing::otherButtonIsPressed(QString coordinates)
{
    QStringList results = coordinates.split(",");
    int row = results.at(0).toInt();
    int column = results.at(1).toInt();
    ui->flagCount->display (this->nrOfMines);
    b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(coordinates));


    if (boardChecker[row][column] == FLAG)
    {
        buttonPressed->setIcon(QIcon(":/plumbus.png"));
        boardChecker[row][column] = 0;
        if (game->getVal(row,column) == MINE)
            this->mineGoal--;
        this->nrOfFlags--;
    }
    else if (!buttonPressed->isFlat() && this->nrOfFlags != this->nrOfMines)
    {
        buttonPressed->setIcon(QIcon(":/poopy.png"));
        if (game->getVal(row,column) == MINE && boardChecker[row][column] == 0)
            this->mineGoal++;
        boardChecker[row][column] = FLAG;
        this->nrOfFlags++;

    }
    //Update the display
    ui->flagCount->display(this->nrOfMines - this->nrOfFlags);
    //qDebug() << this->mineGoal;
    if (this->mineGoal == this->nrOfMines)
        winCase();
}

void testing::setIcon(b *buttonToSet, int row, int column)
{
    //Här sätter jag rätt ikon beroende på om det är en siffra/bomb/osv
    //Är det en nolla sätts en "tom" ruta
    if (game->getVal(row,column) == 0)
    {
        buttonToSet->setIcon(QIcon(":/plumbusCleared.png"));
        buttonToSet->setIconSize(QSize(40,40));
    }
    //Är det en etta sätts en etta ut.
    else if (game->getVal(row,column) == 1)
    {
        buttonToSet->setIcon(QIcon(":/Drawing.png"));
        buttonToSet->setIconSize(QSize(40,40));
    }
    //Är det en tvåa sätts en tvåa ut
    else if (game->getVal(row,column) == 2)
    {
        buttonToSet->setIcon(QIcon(":/two.png"));
        buttonToSet->setIconSize(QSize(40,40));
    }
    //Är det en 3:a sätts en trea ut
    else if (game->getVal(row, column) == 3)
    {
        buttonToSet->setIcon(QIcon(":/three.png"));
        buttonToSet->setIconSize(QSize(40,40));
    }
    //Är det en 4:a sätts en 4a ut
    else if (game->getVal(row,column) == 4)
    {
        buttonToSet->setIcon(QIcon(":/four.png"));
        buttonToSet->setIconSize(QSize(40,40));
    }

    //Är det en mina ska en mina sättas ut.
    else if (game->getVal(row,column) == MINE)
    {
        buttonToSet->setIcon(QIcon(":/Gazorpazorpfield_Bitch.png"));
        buttonToSet->setIconSize(QSize(40,40));
    }
}

void testing::revealClose(int row, int column)
{
    int tempDiff = 0;
    if (this->gameMode == 10)
        tempDiff = 4;
    if (this->gameMode == 20)
        tempDiff = 6;
    if (this->gameMode == 30)
        tempDiff = 8;
    QString tempCoord = "";
    //Måste kolla så att de närliggande inte redan är nedtryckta före jag kör min reveal
    // Fixar fram knappen så att jag kan byta ikon på den osv.
    QString coordinates = QString::number(row) + "," + QString::number(column);
    b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(coordinates));
    //Sätter knappen nedtryckt.
    buttonPressed->setFlat(true);
    //Byter ikon
    this->setIcon(buttonPressed, row, column);

    // vänstra övre hörn
    if ( (row - 1) != -1 && (column - 1) != -1)
    {
        tempCoord = QString::number(row-1) + "," + QString::number(column-1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row-1, column-1);
    }
    // övre mitt
    if ( (row - 1) != -1)
    {
        tempCoord = QString::number(row-1) + "," + QString::number(column);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row-1, column);
    }
    // höger övre hörn
    if ( (row - 1) != -1 && (column + 1) != tempDiff)
    {
        tempCoord = QString::number(row-1) + "," + QString::number(column+1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row-1, column+1);
    }
    // vänster
    if ( (column - 1) != -1)
    {
        tempCoord = QString::number(row) + "," + QString::number(column-1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row, column-1);
    }
    // höger
    if ( (column + 1) != tempDiff)
    {
        tempCoord = QString::number(row) + "," + QString::number(column+1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row, column+1);
    }
    // nedre vänster hörn
    if ( (row + 1) != tempDiff && (column - 1) != -1)
    {
        tempCoord = QString::number(row+1) + "," + QString::number(column-1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row+1, column-1);
    }
    // nedre mitt
    if ( (row + 1) != tempDiff)
    {
        tempCoord = QString::number(row+1) + "," + QString::number(column);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row+1, column);
    }
    // nedre högra hörn
    if ( (row + 1) != tempDiff && (column + 1) != tempDiff)
    {
        tempCoord = QString::number(row+1) + "," + QString::number(column+1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row+1, column+1);
    }
}

void testing::winCase()
{
    this->timer->stop();
    int secs = 0;
    int mins = 0;
    int tempTimer = this->timeSinceStart;
    mins = tempTimer / 60;
    secs = tempTimer % 60;
    this->isAWin = true;
    this->box = new QMessageBox(this);
    box->setText("H-H-H-HEY, YOU MANAGED TO AVOID ALL OF THE GAZORPAZORPFIELDS\nWAY TO GO BOY!\nYOU'RE WINNER!\nYour time was: " + QString::number(mins) + ":" + QString::number(secs));
    box->setStandardButtons(QMessageBox::Ok);
    box->exec();
    this->close();
}

void testing::loseCase()
{
    this->box = new QMessageBox(this);
    box->setText("L O S E R\nO\nS\nE\nR");
    box->setStandardButtons(QMessageBox::Ok);
    box->exec();
    this->close();
}

void testing::refreshTime()
{
    this->timeSinceStart++;
    ui->gameTimer->display(this->timeSinceStart);
}
