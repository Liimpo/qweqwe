#include "testing.h"
#include "ui_testing.h"
#include "QDebug"
#include "QTextEdit"
#include "QWidget"
#include "piece.h"
#include "QGridLayout"
#include <QString>

#define SPLITTER ","

testing::testing(QWidget *parent, int mineNr, int startSize) :
    QDialog(parent),
    ui(new Ui::testing)
{
    this->nrOfMines = mineNr;
    this->sizeOfBoard = startSize;
    //If this reaches nrOfMines u win.
    this->mineGoal = 0;

    ui->setupUi(this);
    ui->flagCount->display (this->nrOfMines);
    //QGridLayout *layout = new QGridLayout;
    //Layout designs
    ui->mineBoard->setSpacing(0);
    ui->mineBoard->setHorizontalSpacing(0);

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

    setIcon(buttonPressed, row, column);
    if (game->isAMine(row, column))
    {
        this->box = new QMessageBox(this);
        box->setText("L O S E R\nO\nS\nE\nR");
        box->setStandardButtons(QMessageBox::Ok);
        box->exec();
        this->close();
    }
    else if (!buttonPressed->isFlat())
        buttonPressed->setFlat(true);
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
    }
    else if (!buttonPressed->isFlat())
    {
        buttonPressed->setIcon(QIcon(":/poopy.jpg"));
        if (game->getVal(row,column) == MINE && boardChecker[row][column] == 0)
            this->mineGoal++;
        boardChecker[row][column] = FLAG;

    }
    qDebug() << this->mineGoal;
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
        buttonToSet->setIcon(QIcon(":/Drawing.jpeg"));
    //Är det en tvåa sätts en tvåa ut
    else if (game->getVal(row,column) == 2)
        buttonToSet->setIcon(QIcon(":/two.jpeg"));
    //Är det en 3:a sätts en trea ut
    else if (game->getVal(row, column) == 3)
        buttonToSet->setIcon(QIcon(":/three.jpeg"));
    //Är det en 4:a sätts en 4a ut
    else if (game->getVal(row,column) == 4)
        buttonToSet->setIcon(QIcon(":/four.jpeg"));

    //Är det en mina ska en mina sättas ut.
    else if (game->getVal(row,column) == MINE)
        buttonToSet->setIcon(QIcon(":/Gazorpazorpfield_Bitch.png"));
}

void testing::winCase()
{
    this->box = new QMessageBox(this);
    box->setText("H-H-H-HEY, YOU MANAGED TO AVOID ALL OF THE GAZORPAZORPFIELD\n WAY TO GO BOY!\nYOU'RE WINNER!");
    box->setStandardButtons(QMessageBox::Ok);
    box->exec();
    this->close();
}
