
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

typedef struct fsm
{
	fsm_state fsm_cur_state;
	calculation_func;
}fsm_t;

typedef struct calc_stack
{
	stack_t *numbers;
	stack_t *operators;
}calc_stack_t;

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

