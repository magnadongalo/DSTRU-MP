#include <stdio.h>
#include <stdbool.h>

struct coordsTag{
    int X,
        Y;
};

typedef struct coordsTag coords;

typedef struct{
    coords stPos;
    int    nCardinality;
} player;

typedef coords grid[3][3];

void emptySet(grid A)
{
    int i, j;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            A[i][j].X = 0;
            A[i][j].Y = 0;
        }
}

bool searchCoords(coords key, grid A)
{
    int i, j;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        if (key.X == A[i][j].X && key.Y == A[i][j].Y)
        {
            return true;
        }
    
    return false;
}

void Remove(coords pos, grid R, grid B, grid S, grid T, bool bGo)
{
    if (bGo)
    {
        R[pos.X - 1][pos.Y - 1].X = 0;
        R[pos.X - 1][pos.Y - 1].Y = 0;
    }
    else
    {
        B[pos.X - 1][pos.Y - 1].X = 0;
        B[pos.X - 1][pos.Y - 1].Y = 0;
    }
    

    S[pos.X - 1][pos.Y - 1].X = 0;
    S[pos.X - 1][pos.Y - 1].Y = 0;

    T[pos.X - 1][pos.Y - 1].X = 0;
    T[pos.X - 1][pos.Y - 1].Y = 0;
}

void Add(coords pos, grid A)
{
    A[pos.X - 1][pos.Y - 1].X = pos.X;
    A[pos.X - 1][pos.Y - 1].Y = pos.Y;
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
            Remove(pos, R, B, S, T, bGo);
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
            Remove(pos, R, B, S, T, bGo);
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

    if(!bGood && searchCoords(pos, S) && !(searchCoords(pos, T)))
    {
        Add(pos, T);
        Expand(pos, R, B, S, T, bGo, bFound);
    }
}

void NextPlayerMove(coords pos, grid R, grid B, grid S, bool bOver, bool bStart, bool bGo, bool bGood)
{
    if (!bOver)
    {
        if (bStart)
        {
            if (bGo)
                Add(pos, R);
            else
                Add (pos, B);
            
            Add(pos, S);
            bGood = true;
        }
        else
        {
            
        }
    }
}

void GameOver()
{

}