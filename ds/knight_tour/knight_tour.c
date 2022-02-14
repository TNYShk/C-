/**********************************************
 * DHCP - C File                               *
 * Developer: Tanya                      *
 * Written:   14/02/2022                       *
 *                                             *
 * Reviewer:                       *
 **********************************************/
#include <stdlib.h> /* malloc() calloc() free() */  /*******/
#include <string.h> /* memset() */

#include <assert.h> /* assert() */
#include <arpa/inet.h>
#include <byteswap.h>

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
    status_t status = SUCCESS;
    uint32_t move = 0;
    unsigned char pos = 0;
    Coor2Pos(x_pos, y_pos, &pos);

    if( !IsInside(x_pos,y_pos) || BitArrayGetVal(board,pos))
        return FAIL;

    board = BitArraySetOn(board, pos);
    Coor2Pos(x_pos, y_pos, tour);
     
     if(64 == BitArrayCountOn(board))
     {
        return SUCCESS;
     }

     for (move = 0; move <  BOARD && status; ++move)
     {
        unsigned char  next_pos = 0;
        Coor2Pos( x_pos + XLUT[move], y_pos + YLUT[move], &next_pos);
        Position2Coor( &x_pos, &y_pos, next_pos);
        status = RecKnightsTour(board,x_pos, y_pos, tour + 1);
     }

     return status;

}

static int IsInside(uint32_t x_pos,uint32_t y_pos)
{
    return ((x_pos < BOARD) && (y_pos < BOARD));
}

static void Position2Coor(uint32_t *x_pos, uint32_t *y_pos, unsigned char pos)
{
    *x_pos = pos & (BOARD - 1);
    *y_pos = pos >> 3;
}

static void Coor2Pos(uint32_t x_pos, uint32_t y_pos, unsigned char *pos)
{
    *pos = (y_pos << 3) + x_pos;
}