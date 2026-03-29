#include "func.c"

int main()
{
    bool bGood = false, bGo = true, bStart = true, bFound = false, bOver = false;
    int nVal = 0;

    coords pos;
    grid R, B, S, T, F;
    playingField display;

    emptySet(&R); emptySet(&B);
    emptySet(&S); emptySet(&T);
    initializePlayingField(display);

    titleScreen();

    showGrid(R, B, display);

    do
    {
        playerTurn(1, &bGo);
        getPos(&pos);
        NextPlayerMove(pos, R, B, S, T, bOver, bStart, bGo, bFound, bGood, nVal);
        showGrid(R, B, display);

        playerTurn(2, &bGo);
        getPos(&pos);
        NextPlayerMove(pos, R, B, S, T, bOver, bStart, bGo, bFound, bGood, nVal);
        showGrid(R, B, display);
    } while (!bOver);
    
    GameOver(bOver, R, B);    

    return 0;
}