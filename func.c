#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#include "main.c"

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

void Expand(coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo, bool bFound);

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
        // PlaySound("red.wav", NULL, SND_ASYNC | SND_FILENAME);
        // Sleep(2500);
        break;
    case 2:
        printf("------BLUE PHASE------\n\n");
        *bGo = false;
        // PlaySound("blue.wav", NULL, SND_ASYNC | SND_FILENAME);
        // Sleep(2500);
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

// UNFINISHED
void updateGrid(coords pos, char string[], grid R, grid B, grid S, grid T, grid F)
{
    if (!F.bTaken[pos.X - 1][pos.Y - 1])
    {
        if (R.bTaken[pos.X - 1][pos.Y - 1])
        {
            if (S.bTaken[pos.X - 1][pos.Y - 1] && !T.bTaken[pos.X - 1][pos.Y - 1])
                strcpy(string, "R1");
            else if (S.bTaken[pos.X - 1][pos.Y - 1] && T.bTaken[pos.X - 1][pos.Y - 1])
                strcpy(string, "R2");
        }
        else if (B.bTaken[pos.X - 1][pos.Y - 1])
        {
            if (S.bTaken[pos.X - 1][pos.Y - 1] && !T.bTaken[pos.X - 1][pos.Y - 1])
                strcpy(string, "B1");
            else if (S.bTaken[pos.X - 1][pos.Y - 1] && T.bTaken[pos.X - 1][pos.Y - 1])
                strcpy(string, "B2");
        }
    }
    else if (F.bTaken[pos.X - 1][pos.Y - 1])
        strcpy(string, "  ");
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

void Remove(coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo)
{
    printf("Passed Remove function\n");

    if (bGo)
        Subtract(pos, R);
    else
        Subtract(pos, B);

    Subtract(pos, S);
    Subtract(pos, T);

    Add(pos, F);
}

void Replace(coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo, bool *bFound)
{
    printf("Passed Replace function\n");

    *bFound = false;

    if (bGo)
    {
        if (searchCoords(pos, *B))
        {
            printf("passed 1");
            Subtract(pos, R);
            *bFound = true;
        }
        else if (searchCoords(pos, *R))
        {
            printf("passed 2");
            *bFound = true;
        }
        else if (!(searchCoords(pos, *R)))
        {
            printf("passed 3");
            Add(pos, R);
            Add(pos, S);

            updateGrid(pos, display[pos.X - 1][pos.Y - 1], R, B, S, T, F);
        }
    }
    else if (!bGo)
    {
        if (searchCoords(pos, *R))
        {
            Subtract(pos, R);
            *bFound = true;
        }
        else if (searchCoords(pos, *B))
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
            Expand(pos, R, B, S, T, F, bGo, *bFound);
        }
    }
}

void Expand(coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo, bool bFound)
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

    Remove(pos, R, B, S, T, F, bGo);

    if (bGo)
        Replace(u, R, B, S, T, F, bGo, &bFound);
    else
        Replace(d, R, B, S, T, F, bGo, &bFound);

    Replace(k, R, B, S, T, F, bGo, &bFound);
    Replace(r, R, B, S, T, F, bGo, &bFound);
}

void Update(coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bGo, bool bFound, bool *bGood)
{
    printf("Passed\n");

    *bGood = false;

    if (!(searchCoords(pos, *S)))
    {
        if (bGo)
        {

            Add(pos, R);
        }

        else
            Add(pos, B);

        Add(pos, S);
        *bGood = true;
    }

    if (!*bGood && searchCoords(pos, *S) && !(searchCoords(pos, *T)))
    {
        if (bGo)
        {
            Add(pos, R);
        }

        else
            Add(pos, B);

        Add(pos, T);
    }
    else if (!*bGood && searchCoords(pos, *S) && (searchCoords(pos, *T)))
    {
        printf("This was an expand turn\n");
        Remove(pos, R, B, S, T, F, bGo);
        Expand(pos, R, B, S, T, F, bGo, bFound);
    }
}

void NextPlayerMove(coords pos, grid *R, grid *B, grid *S, grid *T, grid *F, bool bOver,
                    bool *bStart, bool *bGo, bool bFound, bool *bGood, int *nVal)
{
    if (!bOver)
    {
        if (*bStart)
        {
            printf("This was Start Turn\n");
            if (*bGo)
            {
                Add(pos, R);
            }

            else
                Add(pos, B);

            Add(pos, S);
            *bGood = true;

            *nVal += 1;
        }
        else if (!*bStart)
        {
            printf("This was Game Turn\n");

            if ((*bGo && searchCoords(pos, *R)) || (!*bGo && searchCoords(pos, *B)))
            {
            }

            Update(pos, R, B, S, T, F, *bGo, bFound, bGood);
        }
        else if (bGood)
        {
            *bGood = false;
            *bGo = false;
        }

        if (*bStart && R->nCardinality == 1 && B->nCardinality == 1)
            *bStart = false;
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