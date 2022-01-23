
#include <stdio.h>    /* printf */
#include <stdlib.h> /* strtod*/
#include <assert.h> /* assert */
#include <ctype.h> /* isspace, isdigit*/
#include <string.h> /* strchr */


#include "../include/cal.h"


int main(void)
{
	double result  = 66.6;
	char *str = "5 - -5";

	Calculator(str, &result);
	printf("result is %f\n",result);
	return 0;
}