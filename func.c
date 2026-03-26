#include <stdio.h>
#include <stdbool.h>

struct coordsTag{
    int X,
        Y;
};

typedef struct coordsTag coords;

typedef struct {
    coords gridField[3][3];
    int    nCardinality;
} grid;

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

void showGrid(grid R, grid B, grid S, grid T)
{
    int i;
    int row;

    printf("+---+---+---+\n");

    row = 1;
    for (i=0; i<3; i++)
    {
        printf("| ");

        if (R.gridField[row][i].X != 0 && R.gridField[row][i].Y != 0)
            printf("X ");
        else if (B.gridField[row][i].X != 0 && B.gridField[row][i].Y != 0)
            printf("O ");
        else
            printf("  ");
    }
    printf("|\n");
    //printf("| %c | %c | %c |");
    printf("+---+---+---+\n");

    row++;
    for (i=0; i<3; i++)
    {
        printf("| ");

        if (R.gridField[row][i].X != 0 && R.gridField[row][i].Y != 0)
            printf("X ");
        else if (B.gridField[row][i].X != 0 && B.gridField[row][i].Y != 0)
            printf("O ");
        else
            printf("  ");
    }
    printf("|\n");
    //printf("| %c | %c | %c |\n");
    printf("+---+---+---+\n");

    row = 1;
    for (i=0; i<3; i++)
    {
        printf("| ");

        if (R.gridField[row][i].X != 0 && R.gridField[row][i].Y != 0)
            printf("X ");
        else if (B.gridField[row][i].X != 0 && B.gridField[row][i].Y != 0)
            printf("O ");
        else
            printf("  ");
    }
    printf("|\n");
    //printf("| %c | %c | %c |\n");
    printf("+---+---+---+\n");
}

void emptySet(grid A)
{
    int i, j;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            A.gridField[i][j].X = 0;
            A.gridField[i][j].Y = 0;
        }

    A.nCardinality = 0;
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