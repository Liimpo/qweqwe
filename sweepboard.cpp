#include "sweepboard.h"
#include <QtMath>
#include <QtGlobal>
#include <QDebug>
#include "time.h"

SweepBoard::SweepBoard(double boardSize)
{
    //Reseting the board.
    this->sizeOfBoard = boardSize;
    int tempSize = sqrt(this->sizeOfBoard);
    //int *tempArr = new int[tempSize][tempSize];
    //qDebug() << tempSize;
    //this->gameArr[tempSize][tempSize];
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            gameArr[i][j] = 0;
            qDebug() << i << " " << j;
        }
    }
    qDebug() << "asd";
    sweepSetup();
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {

           qDebug() << getVal(j,i) << getVal(j+1,i) << getVal(j+2,i) << getVal(j+3,i) << getVal(j+4,i) << getVal(j+5,i) << getVal(j+6,i) << getVal(j+7,i);
            if (j == 0)
                j = 8;
        }
    }
}
//Destruktor
SweepBoard::~SweepBoard()
{

}

void SweepBoard::sweepSetup()
{
    qsrand(time(NULL));
    for(int i = 0; i < 9; i++)
    {
        int row, column;
        do
        {
            row = qrand()% 8;
            column = qrand()% 8;
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
        if ( (row-1) != -1 && (column+1) != -1 && gameArr[row-1][column+1] != MINE)
            gameArr[row-1][column+1]++;

        // [][][]
        // [X][][]
        // [][][]
        if ((column-1) != -1 && gameArr[row][column-1] != MINE)
            gameArr[row][column-1]++;

        // [][][]
        // [][][x]
        // [][][]
        if ((column+1) != 8 && gameArr[row][column+1] != MINE)
            gameArr[row][column+1]++;

        // [][][]
        // [][][]
        // [x][][]
        if ((row+1) != 8 && (column-1) != -1 && gameArr[row+1][column-1] != MINE)
            gameArr[row+1][column-1]++;

        // [][][]
        // [][][]
        // [][x][]
        if ((row+1) != 8 && gameArr[row+1][column] != MINE)
            gameArr[row+1][column]++;

        // [][][]
        // [][][]
        // [][][x]
        if ((row+1) != 8 && (column+1) != 8 && gameArr[row+1][column+1] != MINE)
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
