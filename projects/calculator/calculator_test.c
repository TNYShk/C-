/**********************************************
 * Calculator - Source File                   *
 * Tanya			                          *
 *          Jan 24, 2022                      *
 *                                            *
 * Reviewer:         	                      *
 **********************************************/
#include <stdio.h>    /* printf */
#include <assert.h> /* assert */

/*
typedef enum
{
    CALC_SUCCESS = 0,
    CALC_MATH_ERROR = 1,
    CALC_ALLOC_ERROR = 2,
    CALC_SYNTAX_ERROR = 3
} calc_status_t;
*/


#include "../include/cal.h" /* program header*/


int main(void)
{
	double result  = 666666666.66666666;
	char *str = "5 - -5";
	calc_status_t stat;

	

	stat = Calculator("5.4 # 66.6 -5 *2", &result);
	printf("5.4 #66.6 -5 *2: result is: %f, calc_stat is %d\n",result, stat);
	
	stat = Calculator("(-5.4*66.6)", &result);
	printf("(-5.4*66.6): result is: %f, calc_stat is %d\n",result, stat);
	
	stat = Calculator("2*[3*(1+2)]-5", &result);
	printf("2*[3*(1+2)]-5: result is: %f,calc_stat is %d\n",result, stat);
	
	stat = Calculator("(5.4+*66.6)", &result);
	printf("not good (5.4+*66.6): result is: %f,calc_stat is %d\n",result, stat);
	

	Calculator("5.4 * 66.6", &result);
	printf("5.4 * 66.6: result is: %f\n",result);
	Calculator(str, &result);
	printf("%s : result is %f\n",str,result);
	Calculator("5.4 / 66.6 -5 *2", &result);
	printf("5.4 / 66.6 -5 *2: result is: %f\n",result);
	Calculator("2+(2^2)", &result);
	printf("2+(2^2) is: %f\n",result);
	Calculator("\n2+3*4", &result);
	printf("2+3*4: result is: %f\n",result);
	


	return 0;
}