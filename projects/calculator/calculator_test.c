
#include <stdio.h>    /* printf */
#include <stdlib.h> /* strtod*/
#include <assert.h> /* assert */
#include <ctype.h> /* isspace, isdigit*/
#include <string.h> /* strchr */
#include <math.h>

#include "../include/cal.h"


int main(void)
{
	double result  = 666666666.66666666;
	char *str = "5 - -5";
	
	Calculator("5.4 # 66.6 -5 *2", &result);
	printf("5.4 #66.6 -5 *2: result is: %f\n",result);
	Calculator("2*[3*(1+2)]-5", &result);
	printf("2*[3*(1+2)]-5: result is: %f\n",result);
	Calculator("(5.4+66.6)", &result);
	printf("(5.4+66.6): result is: %f\n",result);
	
	
	Calculator("5.4 * 66.6", &result);
	printf("5.4 * 66.6: result is: %f\n",result);
	Calculator(str, &result);
	printf("%s : result is %f\n",str,result);
	Calculator("5.4 / 66.6 -5 *2", &result);
	printf("5.4 / 66.6 -5 *2: result is: %f\n",result);
	Calculator("2+2^2", &result);
	printf("2+2^2 is: %f\n",result);
	Calculator("\n2+3*4", &result);
	printf("2+3*4: result is: %f\n",result);
	

	return 0;
}