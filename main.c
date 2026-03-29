#include "func.c"

int main()
{
    bool bGood = false, bGo = true, bStart = true, bFound = false, bOver = false;
    int nVal = 0, i = 0, nTurn = 1;

    coords pos;
    grid R, B, S, T, F;
    playingField display;

    emptySet(&R);
    emptySet(&B);
    emptySet(&S);
    emptySet(&T);
    fillSet(&F);
    initializePlayingField(display);

    titleScreen();

    // showGrid(R, B, display);

    do
    {
        
        if (i % 2 == 0)
            nTurn = 1;
        if (i % 2 == 1)
            nTurn = 2;

        playerTurn(nTurn, &bGo);
        showGrid(display);

        printf("Turn %d\n", nVal);

        getPos(&pos);

        NextPlayerMove(display, pos, &R, &B, &S, &T, &F, bOver, &bStart, &bGo, bFound, &bGood, &nVal);
        updateF(&F, &R, &B);

        //F.nCardinality = 9 - R.nCardinality + B.nCardinality;
        updateGrid(display, R, B, S, T, F);

        i++;

        if ((F.nCardinality <= 3 || nVal >= 20 || !bStart) && ((R.nCardinality > 0 && B.nCardinality == 0) || (R.nCardinality == 0 && B.nCardinality > 0)))
            bOver = true;

    } while (!bOver);

    GameOver(bOver, R, B);

    return 0;
}