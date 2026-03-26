#include "func.c"
#include <windows.h>

int main()
{
    bool bGood = false, bGo = true, bStart = true, bFound = false, bOver;
    int nVal = 0;

    coords pos;
    grid R, B, S, T;

    emptySet(R); emptySet(B);
    emptySet(S); emptySet(T);

    do
    {
        printf("The game begins!\n");
        Sleep(3000);

        showGrid(R, B, S, T);
    } while (!bOver);
    
    GameOver(bOver, R, B);    

    return 0;
}