/**********************************************
 * Calculator - Source File                   *
 * Tanya			                          *
 *          Jan 24, 2022                      *
 *                                            *
 * Reviewer:         	                      *
 **********************************************/
#include <stdlib.h> /* memory allocation*/
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include <math.h> /* power */

#include "../include/cal.h" /* program header */
#include "../include/stack.h" /* required module */
#include "../include/pars.h" /* required module */

#define ASCII (128)
#define BADOP ('@')	



typedef enum state
{
	WAIT_NUM,
	WAIT_OP,
	INVALID

}state_t;


typedef struct calc_stack
{
	stack_t *numbers;
	stack_t *operators;
	state_t cur_state;

}calc_stack_t;


/* typedef funcs */
typedef calc_status_t (*operation_func_t)(calc_stack_t *);
typedef int (*state_func_t)(char **, calc_status_t *, operation_func_t *, int *, calc_stack_t *);

/*** service funs ***/
static int IsRightParanthesis(char c);
static void InitOperatorsLut(operation_func_t *operators_lut);
static void InitPrecedenceTable(int *precedence_lut);

static int StateGetNumber(char **math_expression, calc_status_t *status, operation_func_t *operators_lut,
	int *precedence_lut, calc_stack_t *calc);
static int StateGetOperator(char **math_expression, calc_status_t *status, operation_func_t *operators_lut,
	int *precedence_lut, calc_stack_t *calc);

static calc_stack_t *IniCalc(size_t len);
static calc_status_t CalcPlus(calc_stack_t *calc);
static calc_status_t CalcMinus(calc_stack_t *calc);
static calc_status_t CalcMultiply(calc_stack_t *calc);
static calc_status_t CalcDivide(calc_stack_t *calc);
static calc_status_t CalcPower(calc_stack_t *calc);
static calc_status_t CalcInvalidOperator(calc_stack_t *calc);
static calc_status_t CalcPresident(calc_stack_t *calc, operation_func_t *operators_lut, char right_president);

static char MatchPresidents(char right_president);
/*** end of service funs ***/




static calc_stack_t *IniCalc(size_t len)
{
	char stam = BADOP;
	double temp = 0;
	stack_t *numbers = NULL;
	stack_t *operators = NULL;
	calc_stack_t *cstack = (calc_stack_t*)malloc(sizeof(calc_stack_t));
	if (NULL == cstack)
	{
		return NULL;
	}

	numbers = StackCreate(len, sizeof(double));
	if (NULL == numbers)
	{
		memset(cstack,0,sizeof(calc_stack_t));
		free(cstack);
		cstack = NULL;
		return NULL;
	}
	operators = StackCreate(len, sizeof(char));
	if (NULL == operators)
	{
		StackDestroy(numbers);
		memset(cstack,0,sizeof(calc_stack_t));
		free(cstack);
		cstack = NULL;
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
	static state_func_t states_lut[] = {StateGetNumber, StateGetOperator};
	static operation_func_t operators_lut[ASCII] = {0};
	static int precedence_lut[ASCII] = {0};

	calc_status_t status = CALC_SUCCESS;
	calc_stack_t *calc = NULL;
	
	char *string_runner = NULL;
	char *string_end = NULL;

	calc = IniCalc(strlen(string));
	if (NULL == calc)
	{
		return CALC_ALLOC_ERROR;
	}

	assert(NULL != string);
	assert(NULL != result);

	InitOperatorsLut(operators_lut);
	InitPrecedenceTable(precedence_lut);
	
	string_runner = (char *)string;
	string_end = string_runner + strlen(string);

	while ( (string_runner <= string_end) && (INVALID != calc->cur_state) )
	{
		calc->cur_state = states_lut[calc->cur_state](&string_runner, &status, 
			operators_lut, precedence_lut, calc);
	}
	if(INVALID == calc->cur_state)
	{
		status = CALC_SYNTAX_ERROR;
	}

	*result = *(double *)StackPeek(calc->numbers);

	StackDestroy(calc->numbers);
	StackDestroy(calc->operators);
	memset(calc,0,sizeof(calc_stack_t));
	free(calc);
	calc = NULL;
	
	return status;	
}





static int StateGetNumber(char **math_expression, calc_status_t *status, operation_func_t *operators_lut,
	int *precedence_lut, calc_stack_t *calc)
{
	double result = 0;
	int ans = ParseNum(*math_expression, math_expression, &result);
	calc->cur_state = WAIT_OP;

	if (READ_OPERATOR == ans )
	{
		StackPush(calc->operators, *math_expression);
		++(*math_expression);
		calc->cur_state = WAIT_NUM;
	}
	else
	{
		StackPush(calc->numbers, &result);
	}
	
	if (INVALID_READ == ans)
	{
		calc->cur_state = INVALID;
		*status = CALC_MATH_ERROR;
	}
	(void)operators_lut;
	(void)precedence_lut;

	return calc->cur_state;
}



static int StateGetOperator(char **math_expression, calc_status_t *status, operation_func_t *operators_lut,
	int *precedence_lut, calc_stack_t *calc)
{
	char new_operator = ' ';
	char prev_operator = ' ';
	int ans = ParseChar1(*math_expression, math_expression, &new_operator);
	
	prev_operator = *(char *)StackPeek(calc->operators);
	
	if(ans == INVALID_READ)
	{
		return INVALID;
	}

	if(IsRightParanthesis(new_operator))
	{
		*status = CalcPresident(calc, operators_lut, new_operator);
		return (CALC_SUCCESS == *status) ? WAIT_OP : INVALID; 
	}

	
	
	while (precedence_lut[(int)prev_operator] > precedence_lut[(int)new_operator])
	{
		*status = operators_lut[(int)prev_operator](calc);
		prev_operator = *(char *)StackPeek(calc->operators);
	}
	
	StackPush(calc->operators, &new_operator);
	
	return (CALC_SUCCESS == *status) ? WAIT_NUM : INVALID; 
}



static void InitOperatorsLut(operation_func_t *operators_lut)
{	
	size_t indx = 0;
	
	for (indx = 0; indx < ASCII; ++indx)
	{
		operators_lut[indx] = CalcInvalidOperator;
	}
	
	operators_lut['+'] = CalcPlus;
	operators_lut['-'] = CalcMinus;
	operators_lut['*'] = CalcMultiply;
	operators_lut['/'] = CalcDivide;
	operators_lut['^'] = CalcPower;
	
}


static void InitPrecedenceTable(int *precedence_lut)
{	
	precedence_lut[BADOP] = -5;		
	
	precedence_lut['('] = 0;
	precedence_lut['{'] = 0;
	precedence_lut['['] = 0;

	precedence_lut['+'] = 1;
	precedence_lut['-'] = 1;
	
	precedence_lut['*'] = 2;
	precedence_lut['/'] = 2;
	
	precedence_lut['^'] = 3;

}


static calc_status_t CalcPlus(calc_stack_t *calc)
{
	double right = 0.0;
	
	StackPop(calc->operators);

	right = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	*(double *)StackPeek(calc->numbers) += right;
	
	return CALC_SUCCESS;
}

static calc_status_t CalcMinus(calc_stack_t *calc)
{
	double right = 0.0;
	
	StackPop(calc->operators);

	right = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	*(double *)StackPeek(calc->numbers) -= right;
	
	
	return CALC_SUCCESS;
}


static calc_status_t CalcMultiply(calc_stack_t *calc)
{
	double right = 0.0;
	
	StackPop(calc->operators);

	right = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	*(double *)StackPeek(calc->numbers) *= right;
	
	return CALC_SUCCESS;
}


static calc_status_t CalcDivide(calc_stack_t *calc)
{
	double right = 0.0;
	
	StackPop(calc->operators);
	right = *(double *)StackPeek(calc->numbers);
	if(0 == right)
	{
		calc->cur_state = INVALID;
		return CALC_MATH_ERROR;
	}
	

	right = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	*(double *)StackPeek(calc->numbers) /= right;
	
	return CALC_SUCCESS;
}

static calc_status_t CalcPower(calc_stack_t *calc)
{
	double right = 0.0;
	double left = 0.0;
	
	right = *(double *)StackPeek(calc->numbers);
	
	StackPop(calc->numbers);
	
	left = *(double *)StackPeek(calc->numbers);
	StackPop(calc->numbers);
	
	left = pow(left,right);
	
	StackPush(calc->numbers, &left);
	StackPop(calc->operators);
	
	return CALC_SUCCESS;
}

static calc_status_t CalcPresident(calc_stack_t *calc, operation_func_t *operators_lut, char right_president)
{
	char left_president = MatchPresidents(right_president);
	calc_status_t temp = CALC_SUCCESS;

	while (left_president != (*(char *)StackPeek(calc->operators)))
	{
		temp = operators_lut[(int)*(char *)StackPeek(calc->operators)](calc);
	}
	StackPop(calc->operators);


	return temp;
}

static calc_status_t CalcInvalidOperator(calc_stack_t *calc)
{
	(void)calc;

	return CALC_SYNTAX_ERROR;
}

static char MatchPresidents(char right_president)
{
    char left_par = '\0';

    switch(right_president)
    {
        case ')':
        left_par = '(';
        break;

        case ']':
        left_par = '[';
        break;

        case '}':
        left_par = '{';
        break;
    }

    return left_par;
}

static int IsRightParanthesis(char c)
{
    return (c == ')') || (c == ']') || (c == '}');
}
/*
static int IsLeftParanthesis(char c)
{
    return (c == '(') || (c == '[') || (c == '{');
}*/
