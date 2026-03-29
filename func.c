#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

struct coordsTag{
    int X,
        Y;
};

typedef struct coordsTag coords;

typedef struct {
    coords gridField[3][3];
    int    nCardinality;
} grid;

typedef char pairedChar[2];
typedef pairedChar playingField[3][3];

void Expand(coords pos, grid R, grid B, grid S, grid T, bool bGo, bool bFound);

void titleScreen()
{
    printf("\n|----------------------------------------------------------------------|\n");

    printf("   ___ _           _         ___                 _   _             \n");
    printf("  / ___| |         ()       |  _ \\               | | ()            \n");
    printf(" | |    | |__   _ _ _ _ _   | |__) |___  _ _  ___| | _  _  _ __  \n");
    printf(" | |    | '_ \\ / _ | | '_ \\  |  _  // _ \\/ _ |/ __| __| |/ _ \\| '_ \\ \n");
    printf(" | |____| | | | (| | | | | | | | \\ \\  __/ (_| | (__| |_| | () | | | |\n");
    printf("  \\_____|_| |_|\\__,_|_|_| |_| |_|  \\_\\___|\\__,_|\\___|\\__|_|\\___/|_| |_|\n");

    printf("\n|----------------------------------------------------------------------|\n\n");
}

void playerTurn(int n, bool *bGo)
{
    switch (n)
    {
    case 1:
            //Red turn!
            *bGo = true;
            //PlaySound("red.wav", NULL, SND_ASYNC | SND_FILENAME);
            Sleep(2500);
        break;
    case 2:
            //Blue turn!
            *bGo = false;
            //PlaySound("blue.wav", NULL, SND_ASYNC | SND_FILENAME);
            Sleep(2500);
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
        printf("Column");
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
    int i, j;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            if (key.X == A.gridField[i][j].X && key.Y == A.gridField[i][j].Y)
            {
                return true;
            }
        
    return false;
}

//UNFINISHED
void updateGrid(playingField grSym, grid M, grid R, grid B)
{
    int i, j;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            if(M.gridField[i][j].X == 0 && M.gridField[i][j].Y == 0)
            {
                if (R.gridField[i][j].X != 0 && R.gridField[i][j].Y != 0)
                    strcpy(grSym[i][j], "R1");
            }
        }
}

void showGrid(grid R, grid B, playingField grSym)
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

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            A->gridField[i][j].X = 0;
            A->gridField[i][j].Y = 0;
        }

    A->nCardinality = 0;
}

void initializePlayingField(playingField A)
{
    int i, j;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            strcpy(A[i][j], "  ");
}

void Remove(coords pos, grid R, grid B, grid S, grid T, bool bGo)
{
    if (bGo)
    {
        R.gridField[pos.X - 1][pos.Y - 1].X = 0;
        R.gridField[pos.X - 1][pos.Y - 1].Y = 0;
        R.nCardinality--;
    }
    else
    {
        B.gridField[pos.X - 1][pos.Y - 1].X = 0;
        B.gridField[pos.X - 1][pos.Y - 1].Y = 0;
        B.nCardinality--;
    }
    

    S.gridField[pos.X - 1][pos.Y - 1].X = 0;
    S.gridField[pos.X - 1][pos.Y - 1].Y = 0;
    S.nCardinality--;

    T.gridField[pos.X - 1][pos.Y - 1].X = 0;
    T.gridField[pos.X - 1][pos.Y - 1].Y = 0;
    T.nCardinality--;
}

void Add(coords pos, grid A)
{
    A.gridField[pos.X - 1][pos.Y - 1].X = pos.X;
    A.gridField[pos.X - 1][pos.Y - 1].Y = pos.Y;
    A.nCardinality++;
}

void Replace(coords pos, grid R, grid B, grid S, grid T, bool bGo, bool bFound)
{
    bFound = false;

    if (bGo)
    {
        if (searchCoords(pos, B))
        {
            B.gridField[pos.X - 1][pos.Y - 1].X = 0;
            B.gridField[pos.X - 1][pos.Y - 1].Y = 0;
            B.nCardinality--;
            bFound = true;
        }
        else if (searchCoords(pos, R))
            bFound = true;
        else if (!(searchCoords(pos, R)))
            Add(pos, R);
    }
    else if (!bGo)
    {
        if (searchCoords(pos, R))
        {
            R.gridField[pos.X - 1][pos.Y - 1].X = 0;
            R.gridField[pos.X - 1][pos.Y - 1].Y = 0;
            R.nCardinality--;
            bFound = true;
        }
        else if (searchCoords(pos, B))
            bFound = true;
        else if (!(searchCoords(pos, B)))
            Add(pos, B);
    }

    if (bFound)
    {
        if (!(searchCoords(pos, S)))
        {
            Add(pos, S);
            bFound = false;
        }
        else if(searchCoords(pos, S) && !(searchCoords(pos, T)))
        {
            Add(pos, T);
            Expand(pos, R, B, S, T, bGo, bFound);
        }
    }
}

void Expand(coords pos, grid R, grid B, grid S, grid T, bool bGo, bool bFound)
{
    coords u, d, k, r;

    //u = (a-1, b)
    u.X = pos.X - 1;
    u.Y = pos.Y;

    //d = (a+1, b)
    d.X = pos.X + 1;
    d.Y = pos.Y;

    //k = (a, b-1)
    k.X = pos.X;
    k.Y = pos.Y - 1;

    //r = (a, b+1)
    r.X = pos.X;
    r.Y = pos.Y -1;

    Remove(pos, R, B, S, T, bGo);

    if (bGo)
        Replace(u, R, B, S, T, bGo, bFound);
    else 
        Replace(d, R, B, S, T, bGo, bFound);

    Replace(k, R, B, S, T, bGo, bFound);
    Replace(r, R, B, S, T, bGo, bFound);
}

void Update(coords pos, grid R, grid B, grid S, grid T, bool bGo, bool bFound, bool bGood)
{
    bGood = false;

    if (!(searchCoords(pos, S)))
    {
        Add(pos, S);
        bGood = true;
    }

    if (!bGood && searchCoords(pos, S) && !(searchCoords(pos, T)))
    {
        Add(pos, T);
        Expand(pos, R, B, S, T, bGo, bFound);
    }
}

void NextPlayerMove(coords pos, grid R, grid B, grid S, grid T, bool bOver, 
                    bool bStart, bool bGo, bool bFound, bool bGood, int nVal)
{
    if (!bOver)
    {
        if (bStart)
        {
            if (bGo)
                Add(pos, R);
            else
                Add(pos, B);
            
            Add(pos, S);
            bGood = true;
        }
        else if (!bStart)
        {
            if (bGo && (searchCoords(pos, R) || !bGo) && searchCoords(pos, B))  
            {
                Update(pos, R, B, S, T, bGo, bFound, bGood);
            } 
        }
        else if (bGood)
        {
            bGood = false;
            bGo = false;
            nVal++;
        }
    }
    else if (bStart && R.nCardinality == 1 && B.nCardinality == 1)
        bStart = false;
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