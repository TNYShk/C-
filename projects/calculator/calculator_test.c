/**********************************************
 * Calculator - Source File                   *
 * Tanya			                          *
 *          Jan 24, 2022                      *
 *                                            *
 * Reviewer:         	                      *
 **********************************************/
#include <stdio.h>    /* printf */
#include <assert.h> /* assert */
#include <math.h> /* power fabs */


#include "../include/cal.h" /* program header*/

static void TestCalcStatus();
static void TestCalculations();


int main(void)
{

	
	TestCalcStatus();
	TestCalculations();
	return 0;
}

static void TestCalcStatus()
{
	double result  = 666666666.66666666;
	printf("\n---------------Calc Status Test-ERRORS----------\n\n");
	assert(Calculator("5.4 # 66.6 -5 *2", &result) ==  CALC_SYNTAX_ERROR);
	printf("5.4 #66.6 -5 *2\n");
	assert(Calculator("5.4@+@*66.6)", &result) ==  CALC_SYNTAX_ERROR);
	printf("5.4@+@*66.6)\n");
	assert(Calculator("(5.4+*66.6)", &result) ==  CALC_SYNTAX_ERROR);
	printf("(5.4+*66.6)\n");
	assert(Calculator("{(5.4+*66.6)", &result) ==  CALC_SYNTAX_ERROR);
	printf("{(5.4+*66.6)\n");
	assert(Calculator("5.4+@*66.6)", &result) ==  CALC_SYNTAX_ERROR);
	printf("5.4+@*66.6)\n");
	assert(Calculator("1+0/0",&result) != CALC_MATH_ERROR);
	printf("1+0/0\n");
	assert(Calculator("[1+0/0@",&result) == CALC_SYNTAX_ERROR);
	printf("[1+0/0@\n");

	printf("\nPassed ERROR STATUS assert Tests\n");
}

static void TestCalculations()
{
	double result = 8888.8;
	double actual_result = 0;
	printf("\n---------------Calc Calculations Test----------\n\n");
	Calculator("(-5.4*66.6)", &result);
	printf("(-5.4*66.6): calculated result is: %f\n",result);
	actual_result = (-5.4*66.6);
	assert(fabs(result)== fabs(actual_result));
	
	Calculator("(0.000007*66.6)", &result);
	printf("(0.000007*66.6): calculated result is: %f\n",result);
	actual_result = (0.000007*66.6);
	assert(fabs(result)== fabs(actual_result));

	Calculator("2*[3/(1+2)]-5", &result);
	printf("2*[3/(1+2)]-5: calculated result is: %f\n",result);
	actual_result = 2*(3/(1+2))-5;
	assert(fabs(result)== fabs(actual_result));

	Calculator("2*[3*(11.5+2)]-5", &result);
	printf("2*[3*(11.5+2)]-5: calculated result is: %f\n",result);
	actual_result = 2*(3*(11.5+2))-5;
	assert(fabs(result)== fabs(actual_result));

	Calculator("-5.4 + 66.6 + 8 -5", &result);
	printf("-5.4 + 66.6 + 8 -5: result is: %f\n",result);
	actual_result = -5.4 + 66.6 + 8 -5;
	assert(fabs(result)== fabs(actual_result));

	Calculator("5.4 / 66.6 -5 *2", &result);
	printf("5.4 / 66.6 -5 *2: result is: %f\n",result);
	actual_result = 5.4 / 66.6 -5 *2;
	assert(fabs(result)== fabs(actual_result));

	Calculator("1+2^3^2+1", &result);
	printf("\n1+2^3^2+1 is: %f\n",result);
	actual_result = 1+pow(2,pow(3,2))+1;
	assert(fabs(result)== fabs(actual_result));

	Calculator("1+2^3+1*2", &result);
	printf("1+2^3+1*2 is: %f\n",result);
	actual_result = 1+pow(2,3)+1*2;
	assert(fabs(result)== fabs(actual_result));

	Calculator("10-2+3", &result);
	printf("10-2+3 is: %f\n",result);
	actual_result = 10-2+3;
	assert(fabs(result)== fabs(actual_result));

	Calculator("10+3-2", &result);
	printf("10+3-2 is: %f\n",result);
	actual_result = 10+3-2;
	assert(fabs(result)== fabs(actual_result));

	Calculator("10*3/2", &result);
	printf("10*3/2 is: %f\n",result);
	actual_result = 10*3/2;
	assert(fabs(result)== fabs(actual_result));

	Calculator("10/2*3", &result);
	printf("10/2*3 is: %f\n",result);
	actual_result = 10/2*3 ;
	assert(fabs(result) == fabs(actual_result));

	printf("\nPassed Calculation assert Tests!!\n");
}