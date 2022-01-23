
#include <stdio.h>    /* printf */
#include <stdlib.h> /* strtod*/
#include <assert.h> /* assert */
#include <ctype.h> /* isspace, isdigit*/
#include <string.h> /* strchr */

#include "stack.h"
#include "cal.h"
#include "pars.h"


#define ASCII (256)
#define BADOP ('~')	

typedef int (*action_func_t)(double left, double right, double *result);
typedef int (*fsm_state_func_t)(calc_stack_t *, char * , char **, double *result);


static int Plus(double left, double right, double *result);
static int Minus(double left, double right, double *result);
static int Multiply(double left, double right, double *result);

/*
typedef enum
{
    CALC_SUCCESS = 0,
    CALC_MATH_ERROR = 1,
    CALC_ALLOC_ERROR = 2,
    CALC_SYNTAX_ERROR = 3
} calc_status_t;
*/
typedef enum state
{
	INVALID,
	WAIT_NUM,
	WAIT_OP,
	STATES

}fsm_state;

typedef struct state_chage
{
	pars_status_p input;
	fsm_state ouput;

}event_t;


typedef struct fsm
{
	event_t input_output;
	fsm_state_func_t calculations;
	event_t fsm_cur_state[STATES];

}fsm_t;

typedef struct calc_stack
{
	stack_t *numbers;
	stack_t *operators;
	fsm_state fsm_cur_state;

}calc_stack_t;



static const fsm_t FiniteStateM[] = 
{
	{INVALID, &Nothing,   { {INVALID_READ , INVALID},
							{READ_NUMBER, INVALID}},
							{READ_OPERATOR, INVALID} },

	{WAIT_NUM, &ProcessNum, { {INVALID_READ, INVALID}, 
							{READ_NUMBER, WAIT_OP},
							{READ_OPERATOR, WAIT_NUM} },

	{WAIT_OP, &ProcessOp,   { {INVALID_READ , INVALID},
							{READ_NUMBER, INVALID}},
							{READ_OPERATOR, WAIT_NUM} }
	
};


int ProcessNum(calc_stack_t *calc, char *string , char **afterparse, double *result)
{
	
}

calc_status_t Calculator(const char *string, double *result)
{


	double temp = 0.0;
	char *runner = NULL;

	calc_stack_t *cstack = (calc_stack_t*)malloc(sizeof(calc_stack_t));
	if (NULL == cstack)
	{
		return CALC_ALLOC_ERROR;
	}

		if(InitStacks(cstack, strlen(string + 1)) == CALC_SUCCESS)
		{
			StackPush(cstack->operators, &BADOP);
			StackPush(cstack->numbers, &temp);
			
			cstack->fsm_cur_state = WAIT_NUM;
		}

if(ParseNum(string,runner,temp))
{
	char ch = ' ';

	while(('\0' != runner) && (ch != '('))
	{
		StackPush(cstack->numbers, temp);
		ch = ParseChar(runner, &runner);
		StackPush(cstack->operators, ch)

	}
}

}




static int InitStacks(calc_stack_t *new, size_t len)
{
	new->numbers = StackCreate(len, sizeof(double));
	if (NULL == new->numbers)
	{
		return CALC_ALLOC_ERROR;
	}
	new->operators = StackCreate(len, sizeof(char));
	if (NULL == new->operators)
	{
		StackDestroy(new->numbers);
		return CALC_ALLOC_ERROR;
	}
	

	return CALC_SUCCESS;
}

static int Plus(double left, double right, double *result)
{
	*result = left + right;
	return CALC_SUCCESS;
}

static int Minus(double left, double right, double *result)
{
	*result = left - right;
	return CALC_SUCCESS;
}

static int Multiply(double left, double right, double *result)
{
	*result = left * right;
	return CALC_SUCCESS;
}

static int Divide(double left, double right, double *result)
{
	*result = left / right;
	return CALC_SUCCESS;
}

static int Power(double left, double right, double *result)
{
	
	return CALC_SUCCESS;
}