
#include <stdio.h>    /* printf */
#include <string.h> /* strlen*/

#include "fsm.h"

typedef struct fsm
{
	fsm_state fsm_cur_state;
	event_t fsm_state_change[2];
}fsm_t;

static const fsm_t FiniteStateM[] = 
{
	{Q0, {{'1', BLACKHOLE}, {'0', Q1}} },
	{BLACKHOLE, {{'1', BLACKHOLE},{'0', BLACKHOLE}} },
	{Q1,{{'1', Q1},{'0', Q2}} },
	{Q2, {{'1', Q1},{'0', Q2}} }
};



int CheckValidity(const char *string)
{
	fsm_state cur_state = Q0;
	size_t length = strlen(string);
	const char *runner = string;
	size_t index = 0;

	while(length && (cur_state != BLACKHOLE))
	{
		while(FiniteStateM[cur_state].fsm_state_change[index].input != *runner)
		{
			++index;
		}
		cur_state =  FiniteStateM[cur_state].fsm_state_change[index].output;

		--length;
		++runner;
		index = 0;
	}

	return cur_state;
}

