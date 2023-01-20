#include "statek.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define N 10
#define M 10
#define DEPTH_MIN 5

int** CreateMatrix( int nRow, int nCol );
void PrintMatrix( int** pTab, int nRow, int nCol );
void DeleteMatrix( int*** pTab );

int main( int argc, char* argv[] )
{
    if( argc != 2 )
    {
        perror( "Brak pliku z glebokosciami!\n" );
        return 1;
    }

    int** pTab = CreateMatrix( N, M );
    if( !pTab )
    {
        perror( "ERROR: Nie przydzielono pamieci dla tablicy z glebokosciami!\n" );
        return 2;
    }

    int** pRoot = CreateMatrix( N, M );
    if( !pRoot )
    {
        perror( "ERROR: Nie przydzielono pamieci dla tablicy z droga do portu!\n" );
        return 3;
    }

    if( !setTab( argv[1], pTab, N, M ) )
    {
        perror( "ERROR: Nie wczytano danych!\n" );
        return 4;
    }

    printf( "Glebokosc morza\n" );
    PrintMatrix( pTab, N, M );

    if( root( pTab, N, M, DEPTH_MIN, 0, 0, pRoot, N - 1, M - 1 ) )
    {
        printf( "Droga do portu:\n" );
        PrintMatrix( pRoot, N, M );
    }
    else printf( "Nie ma mozliwosci doplynac do portu!\n" );

    DeleteMatrix( &pTab );
    DeleteMatrix( &pRoot );
    return 0;
}

int** CreateMatrix( int nRow, int nCol )
{
    int** pTab = (int**)malloc( nRow * sizeof( int* ) );
    if( !pTab ) return NULL;
    memset( pTab, 0, nRow * sizeof( int* ) );
    int** p1 = pTab;

    int* p2 = (int*)malloc( nRow * nCol * sizeof( int ) );
    if( !p2 ) return NULL;
    memset( p2, 0, nRow * nCol * sizeof( int ) );

    for( int i = 0; i < nRow; i++, p2 += nCol )
    {
        *p1++ = p2;
    }

    return pTab;
}

void PrintMatrix( int** pTab, int nRow, int nCol )
{
    int* p = *pTab;
    for( int i = 0; i < nRow; i++ )
    {
        for( int j = 0; j < nCol; j++ )
        {
            printf( "%3d ", *p++ );
        }
        printf( "\n" );
    }
}

void DeleteMatrix( int*** pTab )
{
    free( **pTab );
    free( *pTab );
    *pTab = NULL;
}