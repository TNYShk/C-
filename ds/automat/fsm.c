#include <assert.h>   /* assert */
#include <stdio.h>    /* printf */
#include <stdlib.h>   /* srand, rand, qsort*/


#define ZERO_ONE(a) (0 != a)

typedef fsm_state (*action_func)(char digit);

typedef enum 
{
	BLACHOLE = -1,
	START,
	Q1,
	Q2

}fsm_state;

typedef enum
{
	ADDZERO,
	ADDONE

}fsm_event;

typedef struct fsm
{
	fsm_state fsm_cur_state;
	fsm_event fsm_event_output
	action_func event_handler;

}fsm_t;

static FiniteStateM[] = 
{
	{START, &Start,ADDZERO,ADDONE },
	{BLACHOLE, &Hole,},
	{Q1, },
	{Q2,}
};


static fsm_state Start(char first)
{
	return((first == 0)? Q1 : BLACHOLE);
}

static fsm_state Hole(char notmatter)
{
	(void)notmatter;
	return BLACHOLE;
}

static fsm_start TwoDigits(char digit)
{
	return((digit == 0) ? Q2 : Q1);
}

