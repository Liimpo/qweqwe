#ifndef SWEEPBOARD_H
#define SWEEPBOARD_H

#define MINE 9
#define FLAG 8
#define EMPTY 0

class SweepBoard
{
public:
    SweepBoard(double boardSize = 0);
    ~SweepBoard();
    bool isAMine(int y = 0, int x = 0);
    int getVal(int y = 0, int x = 0);

private:
    double sizeOfBoard = 0;
    void sweepSetup();
    int gameArr[8][8];
};

#endif // SWEEPBOARD_H
