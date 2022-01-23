
#include <stdio.h>    /* printf */
#include <stdlib.h> /* strtod*/
#include <assert.h> /* assert */
#include <ctype.h> /* isspace, isdigit*/
#include <string.h> /* strchr */

#include "../include/stack.h"
#include "../include/cal.h"
#include "../include/pars.h"


#define ASCII (128)
#define BADOP ('@')	




/*
typedef enum
{
    CALC_SUCCESS = 0,
    CALC_MATH_ERROR = 1,
    CALC_ALLOC_ERROR = 2,
    CALC_SYNTAX_ERROR = 3
} calc_status_t;

typedef enum pars_status
{
	INVALID_READ, -1
	READ_NUMBER, = DOUBLE
	READ_OPERATOR = CHAR
	
}pars_status_p;

*/


typedef enum state
{
	
	WAIT_NUM,
	WAIT_OP,
	INVALID,
	STATES

}state_t;


typedef struct calc_stack
{
	stack_t *numbers;
	stack_t *operators;
	state_t cur_state;

}calc_stack_t;

typedef calc_status_t (*operation_func_t)(calc_stack_t *);
typedef int (*state_func_t)(char **, calc_status_t *, operation_func_t *, int *, calc_stack_t *);

static void InitOperatorsLut(operation_func_t *operators_lut);
static void InitValidOperators(operation_func_t *operators_lut);
static void InitPrecedenceTable(int *precedence_table);

static int StateGetNumber(char **math_expression, calc_status_t *status, operation_func_t *operators_lut,
	int *precedence_table, calc_stack_t *calc);

static int StateGetOperator(char **math_expression, calc_status_t *status, operation_func_t *operators_lut,
	int *precedence_table, calc_stack_t *calc);



static calc_stack_t *IniCalc(size_t len);

static calc_status_t CalcPlus(calc_stack_t *calc);
static calc_status_t CalcMinus(calc_stack_t *calc);
static calc_status_t CalcMultiply(calc_stack_t *calc);
static calc_status_t CalcDivide(calc_stack_t *calc);

static calc_status_t CalcInvalidOperator(calc_stack_t *calc);
static calc_status_t CalcDoNothing(calc_stack_t *calc);




static calc_stack_t *IniCalc(size_t len)
{
	char stam = BADOP;
	double temp = 0.0;
	calc_stack_t *cstack = (calc_stack_t*)malloc(sizeof(calc_stack_t));
	stack_t *numbers = NULL;
	stack_t *operators = NULL;

	if (NULL == cstack)
	{
		return NULL;
	}

	numbers = StackCreate(len, sizeof(double));
	if (NULL == numbers)
	{
		free(cstack);
		return NULL;
	}
	operators = StackCreate(len, sizeof(char));
	if (NULL == operators)
	{
		free(cstack);
		StackDestroy(numbers);
		return NULL;
	}

	cstack->numbers = numbers;
	cstack->operators = operators;
	cstack->cur_state = WAIT_NUM;
	StackPush(cstack->operators, &stam);
	StackPush(cstack->numbers, &temp);



	return cstack;
}


calc_status_t Calculator(const char *string, double *result)
{

	state_func_t states_lut[] = {StateGetNumber, StateGetOperator};
	operation_func_t operators_lut[ASCII] = {0};
	int precedence_table[ASCII] = {0};

	calc_status_t status = CALC_SUCCESS;
	int state = WAIT_NUM;
	calc_stack_t *calc = NULL;
	
	char *string_runner = NULL;
	const char *runner_end = NULL;

	

	calc = IniCalc(strlen(string));
	if (NULL == calc)
	{
		return CALC_ALLOC_ERROR;
	}

	assert(NULL != string);
	assert(NULL != result);
	
	
	InitOperatorsLut(operators_lut);
	InitPrecedenceTable(precedence_table);
	
	string_runner = (char *)string;
	runner_end = string + strlen(string);
	
	while ((string_runner <= runner_end) && (INVALID != state))
	{
		state = states_lut[state](&string_runner, &status, 
			operators_lut, precedence_table, calc);
	}
	
	*result = *(double *)StackPeek(calc->numbers);

	StackDestroy(calc->numbers);
	StackDestroy(calc->operators);
	
	return status;	
}





static int StateGetNumber(char **math_expression, calc_status_t *status, operation_func_t *operators_lut,
	int *precedence_table, calc_stack_t *calc)
{
	double result = 0;
	state_t next_state = WAIT_OP;
	
	
	ParseNum(*math_expression, math_expression, &result);
	/**math_expression = ParseNum(*math_expression, &number);*/
	StackPush(calc->numbers, &result);
	
	if (NULL == *math_expression)
	{
		calc->cur_state = INVALID;
		*status = CALC_SYNTAX_ERROR;
	}
	
	return next_state;
}



static int StateGetOperator(char **math_expression, calc_status_t *status, operation_func_t *operators_lut,
	int *precedence_table, calc_stack_t *calc)
{
	char new_operator = 0;
	char prev_operator = 0;
	
	prev_operator = *(char *)StackPeek(calc->operators);
	*math_expression = ParseChar2(*math_expression, &new_operator);
	
	
	while (precedence_table[(int)prev_operator] >= precedence_table[(int)new_operator])
	{
		*status = operators_lut[(int)prev_operator](calc);
		prev_operator = *(char *)StackPeek(calc->operators);
	}
	
	StackPush(calc->operators, &new_operator);
	
	return (CALC_SUCCESS == *status) ? WAIT_NUM : INVALID;
}


static void InitOperatorsLut(operation_func_t *operators_lut)
{	
	size_t loop_index = 0;
	
	assert(NULL != operators_lut);
	
	for (; loop_index < ASCII; ++loop_index)
	{
		operators_lut[loop_index] = CalcInvalidOperator;
	}
	
	InitValidOperators(operators_lut);
}

static void InitValidOperators(operation_func_t *operators_lut)
{	
	assert(NULL != operators_lut);
	
	operators_lut[BADOP] = CalcDoNothing;

	operators_lut['+'] = CalcPlus;
	operators_lut['-'] = CalcMinus;
	operators_lut['*'] = CalcMultiply;
	operators_lut['/'] = CalcDivide;
}


static void InitPrecedenceTable(int *precedence_table)
{	
	precedence_table['@'] = -5;		/* dummy operator */
	
	precedence_table['+'] = 1;
	precedence_table['-'] = 1;
	
	precedence_table['*'] = 2;
	precedence_table['/'] = 2;
	
	precedence_table['^'] = 3;
	
	precedence_table['('] = 4;
	precedence_table['{'] = 4;
	precedence_table['['] = 4;
}


static calc_status_t CalcPlus(calc_stack_t *calc)
{
	double right = 0.0;
	double left = 0.0;
	
	assert(NULL != calc->numbers);
	assert(NULL != calc->operators);
	
	right = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	left = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	left += right;
	
	StackPush(calc->numbers, &left);
	StackPop(calc->operators);
	
	return CALC_SUCCESS;
}


static calc_status_t CalcMinus(calc_stack_t *calc)
{
	double right = 0.0;
	double left = 0.0;
	
	assert(NULL != calc->numbers);
	assert(NULL != calc->operators);
	
	right = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	left = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	left-= right;
	
	StackPush(calc->numbers, &left);
	StackPop(calc->operators);
	
	return CALC_SUCCESS;
}


static calc_status_t CalcMultiply(calc_stack_t *calc)
{
	double right = 0.0;
	double left = 0.0;
	
	assert(NULL != calc->numbers);
	assert(NULL != calc->operators);
	
	right = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	left = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	left*= right;
	
	StackPush(calc->numbers, &left);
	StackPop(calc->operators);
	
	return CALC_SUCCESS;
}


static calc_status_t CalcDivide(calc_stack_t *calc)
{
	double right = 0.0;
	double left = 0.0;
	
	assert(NULL != calc->numbers);
	assert(NULL != calc->operators);
	
	right = *(double *)StackPeek(calc->numbers);
	if(0.0 == right)
	{
		return CALC_MATH_ERROR;
	}
	StackPop(calc->numbers);
	
	left = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	left/= right;
	
	StackPush(calc->numbers, &left);
	StackPop(calc->operators);
	
	return CALC_SUCCESS;
}

static calc_status_t CalcInvalidOperator(calc_stack_t *calc)
{
	(void)calc;

	return CALC_SYNTAX_ERROR;
}



static calc_status_t CalcDoNothing(calc_stack_t *calc)
{
	(void)calc;
	
	
	return CALC_SUCCESS;
}
