/**********************************************
 * DHCP - C File                               *
 * Developer: Tanya                            *
 * Written:   14/02/2022                       *
 *                                             *
 * Reviewer:                       *
 **********************************************/
#include <stdlib.h> /* malloc() calloc() free() */  /*******/
#include <string.h> /* memset() */
#include <stdio.h>
#include <stdint.h>
#include <limits.h> /*for LONG_MAX */
#include <assert.h> /* assert() */


#include "knight_tour.h"
#include "bit_array.h"

#define BOARD (8)
 
typedef enum status
{
    SUCCESS = 0,
    FAIL = 1
}status_t;

                                
static const char XLUT[] = {2, 2, -2, -2, 1, 1, -1, -1};
static const char YLUT[] = {1, -1, 1, -1, 2, -2, 2, -2};



static int IsInside(uint32_t x_pos,uint32_t y_pos);
static void Position2Coor(uint32_t *x_pos, uint32_t *y_pos, unsigned char pos);
static void Coor2Pos(uint32_t x_pos, uint32_t y_pos, unsigned char *pos);
static status_t RecKnightsTour(bits_arr64_t board, uint32_t x_pos, uint32_t y_pos, unsigned char *tour);


void KnightsTour(unsigned char pos, unsigned char *tour)
{
    bits_arr64_t board = 0;
    uint32_t x_pos = 0; 
    uint32_t y_pos = 0;

    assert(NULL != tour);
    assert(64 > pos);

    board = BitArrayResetAll(board);
    tour[0] = pos;
    Position2Coor(&x_pos, &y_pos, pos);
    RecKnightsTour(board, x_pos, y_pos, tour + 1);
}

static status_t RecKnightsTour(bits_arr64_t board, uint32_t x_pos, uint32_t y_pos, unsigned char *tour)
{
    status_t status = FAIL;
    uint32_t move = 0;
    unsigned char pos = 0;
    Coor2Pos(x_pos, y_pos, &pos);
    
    Position2Coor(&x_pos, &y_pos, pos);
   
    if(BitArrayGetVal(board,pos))
    {
        return FAIL;
    }

     
     if(64 == BitArrayCountOn(board))
     {
        return SUCCESS;
     }
     
    board = BitArraySetOn(board, pos);
    *tour = pos;

     for (move = 0; move <  BOARD && (status == FAIL) ; ++move)
     {
        uint32_t next_x = x_pos + XLUT[move];
        uint32_t next_y = y_pos + YLUT[move];

        if (IsInside(next_x, next_y))
        {
             printf("x is %d y is: %d\n",next_x,next_y );
            status = RecKnightsTour(board, next_x, next_y, tour + 1);
        }
     
     }

     return status;

}

static int IsInside(uint32_t x_pos,uint32_t y_pos)
{
    return ((x_pos >= 0 && y_pos >= 0) && (x_pos < BOARD && y_pos < BOARD));
    /*return ((x_pos < BOARD) && (y_pos < BOARD));*/
}

static void Position2Coor(uint32_t *x_pos, uint32_t *y_pos, unsigned char pos)
{
    *x_pos = pos & (BOARD - 1);
    *y_pos = pos >> 3;
    /*printf("x is %d y is %d\n", *x_pos, *y_pos);*/
}

static void Coor2Pos(uint32_t x_pos, uint32_t y_pos, unsigned char *pos)
{
    *pos = (y_pos << 3) + x_pos;
}
/*
static Warnsdorffs(bits_arr64_t board, uint32_t x_pos, uint32_t y_pos,unsigned char *tour)
{
    uint32_t x = x_pos, y = x_pos;
    int i = 0;
    unsigned char pos = 0;
    Coor2Pos(x_pos, y_pos, &pos);
    board = BitArraySetOn(board, pos);

    for (i = 0; i< 64; ++i)
    {
        if (Move_process(board,&x_pos, &y_pos, tour) == 0)
        {
            return SUCCESS;
        }
    }
    if (Neighbour(x_pos, y_pos, x, y) == 0)
    {
        return SUCCESS;
    }
    Printresult(tour)
}

static void Printresult(unsigned char *tour)
{
    int i = 0, j = 0;
    for (i = 0; i < BOARD; ++i)
    {
        for (j = 0; j < BOARD; ++j)
        {
            printf("%d\t", tour[j * BOARD + i]);
        }
        printf("\n");
    }
}

static status_t Move_process(bits_arr64_t board, uint32_t *x_pos, uint32_t *y_pos,unsigned char *tour)
{
    int start = rand() % BOARD, count = 0, i = 0, flag = -1, c = 0, min = (BOARD + 1);
    int next_x = 0, next_y = 0;
    for (count = 0; count < BOARD; ++count)
    {
        unsigned char pos = 0;
        i = (start + count ) % BOARD;

        next_x = *x_pos + XLUT[i];
        next_y = *y_pos + YLUT[i];
         Coor2Pos(next_x, next_y, &pos);
        if (BitArrayGetVal(board, pos))
    }
}
*/