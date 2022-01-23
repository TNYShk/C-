#ifndef __FSM_H__
#define __FSM_H__


typedef enum 
{
	Q0,
	BLACKHOLE,
	Q1,
	Q2

}fsm_state;

typedef struct event
{
	char input;
	fsm_state output;

}event_t;


int CheckValidity(const char *string);




#endif 
/* __PARS_H__ */