/**********************************
 * Knights - C File               *
 * Developer: Tanya               *
 * Written:   15/02/2022          *
 *                                *
 * Reviewer:  Gal T               *
 **********************************/
#include <stdint.h> /* uint32_t*/
#include <stdlib.h> /*qsort */
#include <assert.h> /* assert() */


#include "knight_tour.h" /* program header*/
#include "bit_array.h"

#define EMPTY (0ul)
#define BOARD (sizeof(char) * 8)
#define CHESSBOARD (sizeof(char) * 64)
#define CORK (sizeof(char) * 69)

typedef enum status
{
    SUCCESS = 0,
    FAIL = -1
}status_t;

                              
static const char moves[] = {2 ,2 ,-2 ,-2 ,-1 ,1 ,-1 ,1 };
static char idxBook[CHESSBOARD][9] = {0};



/* service functions */
static int IsInside(uint32_t x_pos,uint32_t y_pos);
static void Position2Coor(uint32_t *x_pos, uint32_t *y_pos, unsigned char pos);
static void Coor2Pos(uint32_t x_pos, uint32_t y_pos, unsigned char *pos);

static status_t RecKnightsTour(bits_arr64_t board, uint32_t x_pos, uint32_t y_pos, unsigned char *tour);
static status_t WarnsdorffRec(bits_arr64_t board, unsigned char pos, unsigned char *tour);

static void InitidxBook(void);
static int GenCmp(const void *pos1,const void *pos2);



void KnightsTour(unsigned char pos, unsigned char *tour)
{
    bits_arr64_t board = 0;
    uint32_t move_x =  0;
    uint32_t move_y = 0;
    
    assert(CHESSBOARD > pos);
    assert(NULL != tour);

    Position2Coor(&move_x, &move_y, pos);
    board = BitArraySetAll(board);
   
    RecKnightsTour(board, move_x, move_y, tour);
  
}


void Warnsdorff(unsigned char pos, unsigned char *tour)
{
    bits_arr64_t board = 0;

    assert(NULL != tour);
    assert(CHESSBOARD > pos);

    board = BitArraySetAll(board);
    
    InitidxBook();
    WarnsdorffRec(board, pos, tour);
}



static void InitidxBook(void)
{
    uint32_t knight_shining_armor = 0;
    uint32_t idx = 0;
 
    for(knight_shining_armor = 0; knight_shining_armor < CHESSBOARD; ++knight_shining_armor)
    {
        uint32_t idxbook_idx = 0;
        uint32_t move_x =  0;
        uint32_t move_y = 0;
       
        Position2Coor(&move_x, &move_y, knight_shining_armor);

        for(idx = 0; idx < BOARD; ++idx)
        {
            uint32_t next_x = move_x + moves[idx];
            uint32_t next_y = move_y + moves[BOARD - 1 - idx];
            
            if (IsInside(next_x, next_y))
            {
                unsigned char pos = 0;
                Coor2Pos(next_x, next_y, &pos);
                idxBook[knight_shining_armor][idxbook_idx] = pos;
                ++idxbook_idx;
            }
        }
        idxBook[knight_shining_armor][idxbook_idx] = CORK;
        qsort(idxBook[knight_shining_armor],idxbook_idx, sizeof(char), &GenCmp);
    }
}

static int GenCmp(const void *left, const void *right)
{
    static const char PossibleMovesLUT[] = 
    {
        2, 3, 4, 4, 4, 4, 3, 2,
        3, 4, 6, 6, 6, 6, 4, 3,
        4, 6, 8, 8, 8, 8, 6, 4,
        4, 6, 8, 8, 8, 8, 6, 4, 
        4, 6, 8, 8, 8, 8, 6, 4,
        4, 6, 8, 8, 8, 8, 6, 4, 
        3, 4, 6, 6, 6, 6, 4, 3,
        2, 3, 4, 4, 4, 4, 3, 2
    };

    return (PossibleMovesLUT[(int)(*(char *)left)] - PossibleMovesLUT[(int)(*(char *)right)]);
}

static status_t WarnsdorffRec(bits_arr64_t board, unsigned char pos, unsigned char *tour)
{
    size_t idx = 0;
    status_t stat = FAIL;
    
    if (EMPTY == board)
    {
        return SUCCESS;
    }
   
    if (0 == BitArrayGetVal(board, pos))
    {
        return FAIL;
    }

    board = BitArraySetOff(board, pos);
    *tour = pos;

    for( ;((stat != SUCCESS) && (idxBook[pos][idx] != CORK)); ++idx)
    {
        stat = WarnsdorffRec(board, idxBook[pos][idx], tour + 1);
    }

    return stat;
}


static status_t RecKnightsTour(bits_arr64_t board, uint32_t x_pos, uint32_t y_pos, unsigned char *tour)
{
    status_t status = FAIL;
    uint32_t idx = 0;
    unsigned char pos = 0;
    Coor2Pos(x_pos, y_pos, &pos);

    if (EMPTY == board)
    {
        return SUCCESS;
    }

    if (0 == BitArrayGetVal(board,pos) )
    {
        return FAIL;
    }

    board = BitArraySetOff(board, pos);
    *tour = pos;
  
    for (idx = 0; idx < BOARD && (status != SUCCESS); ++idx)
    {
        uint32_t next_x = x_pos + moves[idx];
        uint32_t next_y = y_pos + moves[BOARD - 1 - idx];
        
        if (IsInside(next_x, next_y))
        {
            status = RecKnightsTour(board, next_x, next_y, tour + 1);
        }
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



