#include "testing.h"
#include "ui_testing.h"
#include "QDebug"
#include "QTextEdit"
#include "QWidget"
#include "piece.h"
#include "QGridLayout"
#include <QString>
#include <QTimer>

testing::testing(QWidget *parent, int mineNr, int startSize) :
    QDialog(parent),
    ui(new Ui::testing)
{
    this->timeSinceStart = 0;
    this->nrOfFlags = 0;
    this->nrOfMines = mineNr;
    this->sizeOfBoard = startSize;
    //If this reaches nrOfMines u win.
    this->mineGoal = 0;

    ui->setupUi(this);
    ui->flagCount->display (this->nrOfMines - this->nrOfFlags);
    //QGridLayout *layout = new QGridLayout;
    //Layout designs
    ui->mineBoard->setSpacing(0);
    ui->mineBoard->setHorizontalSpacing(0);
    //Här kommer gametimern som ska fixa med hiscore
    ui->gameTimer->setDigitCount(2);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshTime()));
    timer->start(1000);

    //Behöver ytterliggare en multi-dim array som håller koll på om knappar är använda
    //Eller om en flagga är uppsatt.
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
            boardChecker[i][j] = 0;
    }

    //Objects location on the board with Signalmapper
    signalMapper = new QSignalMapper(this);
    signalMapper2 = new QSignalMapper(this);

    //creates a new board
    this->game = new SweepBoard(64);
    //int cnt = 0;
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
            QString coordinates = QString::number(i)+","+QString::number(j);
            //Setting the coordinates.
            signalMapper->setMapping(ptr, coordinates);
            signalMapper2->setMapping(ptr, coordinates);
            connect(ptr, SIGNAL(leftClicked()), signalMapper, SLOT(map()));
            connect(ptr, SIGNAL(rightClicked()), signalMapper2, SLOT(map()));
        }
    }
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
    b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(coordinates));
    QStringList results = coordinates.split(",");
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
        buttonToSet->setIcon(QIcon(":/plumbusCleared.png"));
    //Är det en etta sätts en etta ut.
    else if (game->getVal(row,column) == 1)
        buttonToSet->setIcon(QIcon(":/Drawing.png"));
    //Är det en tvåa sätts en tvåa ut
    else if (game->getVal(row,column) == 2)
        buttonToSet->setIcon(QIcon(":/two.png"));
    //Är det en 3:a sätts en trea ut
    else if (game->getVal(row, column) == 3)
        buttonToSet->setIcon(QIcon(":/three.png"));
    //Är det en 4:a sätts en 4a ut
    else if (game->getVal(row,column) == 4)
        buttonToSet->setIcon(QIcon(":/four.png"));

    //Är det en mina ska en mina sättas ut.
    else if (game->getVal(row,column) == MINE)
        buttonToSet->setIcon(QIcon(":/Gazorpazorpfield_Bitch.png"));
}

void testing::revealClose(int row, int column)
{
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
    if ( (row - 1) != -1 && (column + 1) != 8)
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
    if ( (column + 1) != 8)
    {
        tempCoord = QString::number(row) + "," + QString::number(column+1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row, column+1);
    }
    // nedre vänster hörn
    if ( (row + 1) != 8 && (column - 1) != -1)
    {
        tempCoord = QString::number(row+1) + "," + QString::number(column-1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row+1, column-1);
    }
    // nedre mitt
    if ( (row + 1) != 8)
    {
        tempCoord = QString::number(row+1) + "," + QString::number(column);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row+1, column);
    }
    // nedre högra hörn
    if ( (row + 1) != 8 && (column + 1) != 8)
    {
        tempCoord = QString::number(row+1) + "," + QString::number(column+1);
        b *buttonPressed = qobject_cast<b*>(signalMapper->mapping(tempCoord));
        buttonPressed->setFlat(true);
        this->setIcon(buttonPressed, row+1, column+1);
    }
}

void testing::winCase()
{
    this->box = new QMessageBox(this);
    box->setText("H-H-H-HEY, YOU MANAGED TO AVOID ALL OF THE GAZORPAZORPFIELD\n WAY TO GO BOY!\nYOU'RE WINNER!\nYour time was: " + QString::number(this->timeSinceStart));
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
