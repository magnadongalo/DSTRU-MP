#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

struct coordsTag
{
    int X,
        Y;
};

typedef struct coordsTag coords;

typedef struct
{
    int nCardinality;
    bool bTaken[3][3];
} grid;

typedef char pairedChar[3];
typedef pairedChar playingField[3][3];

void Expand(playingField display, coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo, bool bFound);

void titleScreen()
{
    char cAction;

    printf("\n|----------------------------------------------------------------------|\n");

    printf("   ___ _           _         ___                 _   _             \n");
    printf("  / ___| |         ()       |  _ \\               | | ()            \n");
    printf(" | |    | |__   _ _ _ _ _   | |__) |___  _ _  ___| | _  _  _ __  \n");
    printf(" | |    | '_ \\ / _ | | '_ \\  |  _  // _ \\/ _ |/ __| __| |/ _ \\| '_ \\ \n");
    printf(" | |____| | | | (| | | | | | | | \\ \\  __/ (_| | (__| |_| | () | | | |\n");
    printf("  \\_____|_| |_|\\__,_|_|_| |_| |_|  \\_\\___|\\__,_|\\___|\\__|_|\\___/|_| |_|\n");

    printf("\n|----------------------------------------------------------------------|\n\n");

    printf("\n\n PRESS \"ENTER\" TO CONTINUE\n\n");
    scanf("%c", &cAction);
}

void playerTurn(int n, bool *bGo)
{
    switch (n)
    {
    case 1:
        printf("------RED PHASE------\n\n");
        *bGo = true;
        //PlaySound("red.wav", NULL, SND_ASYNC | SND_FILENAME);
        //Sleep(2500);
        break;
    case 2:
        printf("------BLUE PHASE------\n\n");
        *bGo = false;
        //PlaySound("blue.wav", NULL, SND_ASYNC | SND_FILENAME);
        //Sleep(2500);
        break;
    }
}

void getPos(coords *pos)
{
    int temp;

    do
    {
        printf("Row: ");
        scanf("%d", &temp);

        if (temp >= 1 && temp <= 3)
            pos->X = temp;
        else
            printf("Invalid input...\n");
    } while (temp < 1 || temp > 3);

    temp = 0;

    do
    {
        printf("Column: ");
        scanf("%d", &temp);

        if (temp >= 1 && temp <= 3)
            pos->Y = temp;
        else
            printf("Invalid input...\n");
    } while (temp < 1 || temp > 3);

    printf("\n");
}

bool searchCoords(coords key, grid A)
{
    if (A.bTaken[key.X - 1][key.Y - 1])
        return true;
    else
        return false;
}

void updateGrid(playingField display, grid R, grid B, grid S, grid T, grid F)
{
    int i, j;
    
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            if (!F.bTaken[i][j])
            {
                if (R.bTaken[i][j])
                {
                    if (S.bTaken[i][j] && !T.bTaken[i][j])
                        strcpy(display[i][j], "R1");
                    else if (S.bTaken[i][j] && T.bTaken[i][j])
                        strcpy(display[i][j], "R2");
                }
                else if (B.bTaken[i][j])
                {
                    if (S.bTaken[i][j] && !T.bTaken[i][j])
                        strcpy(display[i][j], "B1");
                    else if (S.bTaken[i][j] && T.bTaken[i][j])
                        strcpy(display[i][j], "B2");
                }
            }
            else if (F.bTaken[i][j])
                strcpy(display[i][j], "  ");
        }
}

void showGrid(playingField grSym)
{
    printf("     c1   c2   c3\n");
    printf("   +----+----+----+\n");
    printf("r1 | %s | %s | %s |\n", grSym[0][0], grSym[0][1], grSym[0][2]);
    printf("   +----+----+----+\n");
    printf("r2 | %s | %s | %s |\n", grSym[1][0], grSym[1][1], grSym[1][2]);
    printf("   +----+----+----+\n");
    printf("r3 | %s | %s | %s |\n", grSym[2][0], grSym[2][1], grSym[2][2]);
    printf("   +----+----+----+\n");
}

void emptySet(grid *A)
{
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            A->bTaken[i][j] = false;

    A->nCardinality = 0;
}

void fillSet(grid *A)
{
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            A->bTaken[i][j] = true;

    A->nCardinality = 9;
}

void initializePlayingField(playingField A)
{
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            strcpy(A[i][j], "  ");
}

void Add(coords pos, grid *A)
{
    A->bTaken[pos.X - 1][pos.Y - 1] = true;
    A->nCardinality += 1;
}

void Subtract(coords pos, grid *A)
{
    A->bTaken[pos.X - 1][pos.Y - 1] = false;
    A->nCardinality -= 1;
}

void updateF(grid *F, grid *R, grid *B)
{
    int i, j;
    coords pos;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            if (R->bTaken[i][j] || B->bTaken[i][j])
            {
                pos.X = i+1;
                pos.Y = j+1;

                Subtract(pos, F);
            }

            if (!R->bTaken[i][j] && !B->bTaken[i][j])
            {
                pos.X = i+1;
                pos.Y = j+1;

                Add(pos, F);
            }
        }
}

void Remove(coords pos, grid *R, grid *B, grid *S, grid *T, bool bGo)
{
    printf("Passed Remove function\n");

    if (bGo)
        Subtract(pos, R);
    else
        Subtract(pos, B);

    Subtract(pos, S);
    Subtract(pos, T);

    //Add(pos, F); grid *F
}

void Replace(playingField display, coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo, bool *bFound)
{
    printf("Passed Replace function\n");

    *bFound = false;

    if (bGo)
    {
        if (searchCoords(pos, *B))
        {
            printf("passed 1");
            Subtract(pos, B);
            *bFound = true;
        }
        
        if (searchCoords(pos, *R))
        {
            printf("passed 2");
            *bFound = true;
        }
        else if (!(searchCoords(pos, *R)))
        {
            printf("passed 3");
            Add(pos, R);
            //Add(pos, S);

            //updateGrid(display[pos.X - 1][pos.Y - 1], *R, *B, *S, *T, *F);
        }
    }
    else if (!bGo)
    {
        if (searchCoords(pos, *R))
        {
            Subtract(pos, R);
            *bFound = true;
        }

        if (searchCoords(pos, *B))
            *bFound = true;
        else if (!(searchCoords(pos, *B)))
            Add(pos, B);
    }

    if (bFound)
    {
        if (!(searchCoords(pos, *S)))
        {
            Add(pos, S);
            *bFound = false;
        }
        else if (searchCoords(pos, *S) && !(searchCoords(pos, *T)))
        {
            Add(pos, T);
            Expand(display, pos, R, B, S, T, F, bGo, *bFound);
        }
    }
}

void Expand(playingField display, coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo, bool bFound)
{
    printf("Passed expand function\n");

    coords u, d, k, r;

    // u = (a-1, b)
    u.X = pos.X - 1;
    u.Y = pos.Y;

    // d = (a+1, b)
    d.X = pos.X + 1;
    d.Y = pos.Y;

    // k = (a, b-1)
    k.X = pos.X;
    k.Y = pos.Y - 1;

    // r = (a, b+1)
    r.X = pos.X;
    r.Y = pos.Y + 1;

    Remove(pos, R, B, S, T, bGo);

    if (bGo)
        Replace(display, u, R, B, S, T, F, bGo, &bFound);
    else
        Replace(display, d, R, B, S, T, F, bGo, &bFound);

    Replace(display, k, R, B, S, T, F, bGo, &bFound);
    Replace(display, r, R, B, S, T, F, bGo, &bFound);
}

void Update(playingField display, coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo, bool bFound, bool *bGood)
{
    printf("Passed\n");

    *bGood = false;

    if (!(searchCoords(pos, *S)))
    {
        Add(pos, S);
        *bGood = !*bGood;
    }

    if (!*bGood && searchCoords(pos, *S) && !(searchCoords(pos, *T)))
    {
        Add(pos, T);
        Expand(display, pos, R, B, S, T, F, bGo, bFound);
    }
    /*else if (!*bGood && searchCoords(pos, *S) && (searchCoords(pos, *T)))
    {
        printf("This was an expand turn\n");
        Remove(pos, R, B, S, T, bGo);
        Expand(display, pos, R, B, S, T, F, bGo, bFound);
    }*/
}

void NextPlayerMove(playingField display, coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bOver,
                    bool *bStart, bool *bGo, bool bFound, bool *bGood, int *nVal)
{
    if (!bOver)
    {
        if (*bStart)
        {
            printf("This was Start Turn\n");
            if (*bGo)
                Add(pos, R); 
            else
                Add(pos, B);    

            Add(pos, S);
            *bGood = true;
        }
        else if (!*bStart)
        {
            printf("This was Game Turn\n");

            if ((*bGo && searchCoords(pos, *R)) || (!*bGo && searchCoords(pos, *B)))
            {
                Update(display, pos, R, B, S, T, F, *bGo, bFound, bGood);
                *bGood = true;
            }            
        }
    }

    if (*bStart && R->nCardinality == 1 && B->nCardinality == 1)
        *bStart = false;

    if (!bOver && *bGood)
    {
        *bGood = !*bGood;
        *bGo = !*bGo;
        *nVal += 1;
    }
}

void GameOver(bool bOver, grid R, grid B)
{
    if (bOver)
    {
        if (R.nCardinality > B.nCardinality)
            printf("That's the game! Red Wins!");
        else if (R.nCardinality < B.nCardinality)
            printf("That's the game! Blue Wins!");
        else if (R.nCardinality == B.nCardinality)
            printf("That's the game! It's a draw!");
    }
}