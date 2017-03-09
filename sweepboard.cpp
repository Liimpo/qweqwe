#include "sweepboard.h"
#include <QtMath>
#include <QtGlobal>
#include <QDebug>
#include "time.h"

SweepBoard::SweepBoard(int boardSize, int mineNr)
{
    //Reseting the board.
    this->sizeOfBoard = boardSize;
    this->nrOfMines = mineNr;
    this->gameArr = new int*[this->sizeOfBoard];
    for (int i = 0; i < this->sizeOfBoard; i++)
    {
        this->gameArr[i] = new int[this->sizeOfBoard];
    }

    for(int i = 0; i < this->sizeOfBoard; i++)
    {
        for(int j = 0; j < this->sizeOfBoard; j++)
        {
            gameArr[i][j] = 0;
            qDebug() << i << " " << j;
        }
    }
    qDebug() << "asd";
    sweepSetup();

    // SKRIVER UT BRÄDET JÄTTEBRA DEBUG FUNKTION!!!
    /*for(int i = 0; i < this->sizeOfBoard; i++)
    {
        for(int j = 0; j < this->sizeOfBoard; j++)
        {

           qDebug() << getVal(j,i) << getVal(j+1,i) << getVal(j+2,i) << getVal(j+3,i); //<< getVal(j+4,i) << getVal(j+5,i); //<< getVal(j+6,i) << getVal(j+7,i);
            if (j == 0)
                j = sizeOfBoard;
        }
    }*/
}
//Destruktor
SweepBoard::~SweepBoard()
{

}

void SweepBoard::sweepSetup()
{
    qsrand(time(NULL));
    for(int i = 0; i < this->nrOfMines; i++)
    {
        int row, column;
        do
        {
            row = qrand()% this->sizeOfBoard;
            column = qrand()% this->sizeOfBoard;
        }while(gameArr[row][column] == MINE);

        gameArr[row][column] = MINE;
        // För att hitta hur många minor som finns i närheten av det klickade området
        // Kör jag igenom alla 8 rutor jämte där minan blev placerad och ökar det värdet med ett.

        // [x][][]
        // [] [MINE][]
        // [][][]
        if ( (row-1) != -1 &&  (column-1) != -1 && gameArr[row-1][column-1] != MINE )
            gameArr[row-1][column-1]++;

        // [][x][]
        // [][][]
        // [][][]
        if ( (row-1) != -1 && gameArr[row-1][column] != MINE)
            gameArr[row-1][column]++;

        // [][][x]
        // [][][]
        // [][][]
        if ( (row-1) != -1 && (column+1) != this->sizeOfBoard && gameArr[row-1][column+1] != MINE)
            gameArr[row-1][column+1]++;

        // [][][]
        // [X][][]
        // [][][]
        if ((column-1) != -1 && gameArr[row][column-1] != MINE)
            gameArr[row][column-1]++;

        // [][][]
        // [][][x]
        // [][][]
        if ((column+1) != this->sizeOfBoard && gameArr[row][column+1] != MINE)
            gameArr[row][column+1]++;

        // [][][]
        // [][][]
        // [x][][]
        if ((row+1) != this->sizeOfBoard && (column-1) != -1 && gameArr[row+1][column-1] != MINE)
            gameArr[row+1][column-1]++;

        // [][][]
        // [][][]
        // [][x][]
        if ((row+1) != this->sizeOfBoard && gameArr[row+1][column] != MINE)
            gameArr[row+1][column]++;

        // [][][]
        // [][][]
        // [][][x]
        if ((row+1) != this->sizeOfBoard && (column+1) != this->sizeOfBoard && gameArr[row+1][column+1] != MINE)
            gameArr[row+1][column+1]++;
    }
}

bool SweepBoard::isAMine(int row, int column)
{
    // CHECKING IF A FLOOR IS HOLDING A MINE
    return gameArr[row][column] == MINE;
}

int SweepBoard::getVal(int row, int column)
{
    return gameArr[row][column];
}
