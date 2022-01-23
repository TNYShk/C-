
#include <stdio.h>    /* printf */
#include <stdlib.h> /* strtod*/
#include <assert.h> /* assert */
#include <ctype.h> /* isspace, isdigit*/
#include <string.h> /* strchr */

#include "stack.h"
#include "cal.h"
#include "pars.h"


#define ASCII (256)


typedef int (*action_func_t)(double left, double right, double *result);
typedef int (*fsm_state_func_t)(calc_status_t status, stack_t *numbers, stack_t *operators,double *result);


static int Plus(double left, double right, double *result);
static int Minus(double left, double right, double *result);

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
	WAIT_NUM,
	WAIT_OP,
	INVALID

}fsm_state;

typedef struct event
{
	fsm_state input;
	alc_status_t output;

}event_t;


typedef struct fsm
{
	
	calculation_func;
	fsm_state fsm_cur_state[3];
}fsm_t;

typedef struct calc_stack
{
	stack_t *numbers;
	stack_t *operators;
}calc_stack_t;



static const fsm_t FiniteStateM[] = 
{
	{WAIT_NUM, {{CALC_SYNTAX_ERROR, INVALID}, {CALC_SUCCESS, WAIT_OP}} },
	{WAIT_OP, {{CALC_MATH_ERROR, INVALID},{CALC_SUCCESS, WAIT_NUM}} },
	{INVALID,{{CALC_SYNTAX_ERROR, INVALID},{CALC_MATH_ERROR, INVALID}} }
};




static const action_func_t calculations[] = { &OpernPars, &OpernPars, &OpernPars,
												&Power, &Multiply, &Divide, &Plus, &Minus, 
											  &ClosePars, &ClosePars,&ClosePars 
											};

calc_status_t Calculator(const char *string, double *result);





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