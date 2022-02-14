/**********************************************
 * DHCP - C File                               *
 * Developer: Tanya                      *
 * Written:   14/02/2022                       *
 *                                             *
 * Reviewer:                       *
 **********************************************/
#include <stdlib.h> /* malloc() calloc() free() */  /*******/
#include <string.h> /* memset() */
#include <stdio.h>

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
static status_t RecKnightsTour(bits_arr64_t, uint32_t pos, unsigned char *tour);


void KnightsTour(unsigned char pos, unsigned char *tour)
{
    bits_arr64_t board = 0;
    

    assert(NULL != tour);
    assert(64 > pos);

    board = BitArrayResetAll(board);
  
    RecKnightsTour(board, pos, tour);
}

static status_t RecKnightsTour(bits_arr64_t board, uint32_t pos, unsigned char *tour)
{
    status_t status = FAIL;
    uint32_t move = 0;
    uint32_t x_pos = 0; 
    uint32_t y_pos = 0;

    Position2Coor(&x_pos, &y_pos, pos);
    printf("x is %d, y is %d\n", x_pos, y_pos);
    printf("is inside? %d\n",IsInside(x_pos,y_pos) );
    
    if( (0 == IsInside(x_pos,y_pos)) || BitArrayGetVal(board,pos))
    {
        printf("fail?\n");
        return FAIL;
    }

    board = BitArraySetOn(board, pos);
    printf("pos is %d\n", pos);
    *tour = pos;
     
     if(64 == BitArrayCountOn(board))
     {
        printf("here\n");
        return SUCCESS;
     }

     for (move = 0; move <  BOARD && (SUCCESS!=status) ; ++move)
     {
        unsigned char next_pos = 0;
        Coor2Pos(x_pos + XLUT[move], y_pos + YLUT[move], &next_pos);
      

        status = RecKnightsTour(board, next_pos, tour + 1);
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