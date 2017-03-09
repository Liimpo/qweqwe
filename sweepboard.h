#ifndef SWEEPBOARD_H
#define SWEEPBOARD_H

#define MINE 9
#define FLAG 8
#define EMPTY 0

class SweepBoard
{
public:
    SweepBoard(int boardSize = 0, int mineNr = 0);
    ~SweepBoard();
    bool isAMine(int y = 0, int x = 0);
    int getVal(int y = 0, int x = 0);

private:
    int nrOfMines;
    int sizeOfBoard;
    void sweepSetup();
    int **gameArr;
};

#endif // SWEEPBOARD_H
