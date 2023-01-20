#include "statek.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef enum { UP, RIGHT, DOWN, LEFT } direction;

int move( int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot )
{
    switch( move )
    {
    case UP:    *px = x - 1; *py = y; break;
    case RIGHT: *py = y + 1; *px = x; break;
    case DOWN:  *px = x + 1; *py = y; break;
    case LEFT:  *py = y - 1; *px = x;
    }
    if( *px >= 0 && *px < nRow && *py >= 0 && *py < nCol )
    {
        if( pTab[*px][*py] > nDepth )                   
        {
            if( !pRoot[*px][*py] ) return 1;            
        }
    }
    return 0;
}

int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest )
{
    static int n = 1;
    pRoot[x][y] = n++;

    if( x == x_dest && y == y_dest ) return 1;

    int new_x = x;                          
    int new_y = y;

    for( int i = UP; i <= LEFT; i++ )      
    {
        if( move( pTab, nRow, nCol, nDepth, i, x, y, &new_x, &new_y, pRoot ) )                     
        {
            if( root( pTab, nRow, nCol, nDepth, new_x, new_y, pRoot, x_dest, y_dest ) ) return 1;  
        }
    }
    pRoot[x][y] = 0;                     
    n--;
    return 0;
}

void clearRoot( int** pRoot, int nRow, int nCol )
{
    memset( *pRoot, 0, nRow * nCol * sizeof( int ) );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol )
{
    FILE* fin = NULL;
    if( !( fin = fopen( sFile, "r" ) ) )
    {
        perror( "Error open input file\n" );
        return 0;
    }

    int* p = *pTab;
    for( int i = 0; i < nRow * nCol; i++ )
    {
        fscanf( fin, "%d", p++ );
    }
    fclose( fin );
    return 1;
}