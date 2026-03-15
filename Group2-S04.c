#include "func.c"

int main()
{
    bool bGood = 0, bGo = 1, bStart = 1, bOver, bFound = 0;
    int nVal = 0;

    coords pos;

    grid R, B, S, T;

    emptySet(R); emptySet(B);
    emptySet(S); emptySet(T);

    if (bGo)
        Remove(pos, R, S, T);
    else if (!bGo)
        Remove(pos, B, S, T);


    if (bGo)
    {
        if ()
    }

    return 0;
}