#include <stdio.h>
#include <stdbool.h>

struct coordsTag{
    int X,
        Y;
};

typedef struct coordsTag coords;

typedef struct{
    coords stPos;
    int    nSize;
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

/*void Remove(coords pos, grid A, grid S, grid T)
{
    A[pos.X - 1][pos.Y - 1].X = 0;
    A[pos.X - 1][pos.Y - 1].Y = 0;

    S[pos.X - 1][pos.Y - 1].X = 0;
    S[pos.X - 1][pos.Y - 1].Y = 0;

    T[pos.X - 1][pos.Y - 1].X = 0;
    T[pos.X - 1][pos.Y - 1].Y = 0;
}*/

void Remove(coords pos, grid A)
{
    A[pos.X - 1][pos.Y - 1].X = 0;
    A[pos.X - 1][pos.Y - 1].Y = 0;
}

void Add(coords pos, grid A)
{
    A[pos.X - 1][pos.Y - 1].X = pos.X;
    A[pos.X - 1][pos.Y - 1].Y = pos.Y;
}

void Replace(coords pos)
{

}

void Expand(coords pos, grid A, grid S, grid T)
{
    coords u, d, k, r;
}

void Update(coords pos)
{

}

NextPlayerMove(coords pos);
GameOver();