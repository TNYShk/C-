#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "pars.h"

int main(void)
{

	char *runner  = NULL;
	char *str = "12.5+5";
	
	double result = 0.0;
	
	printf("int is %d\n",ParseNum(str,&runner,&result));
	printf("parsed is: %f\n", result);
	printf("rest ptr is %s\n", runner);
	printf("char %c parsed\n", ParseChar(runner, &runner));
	printf("rest ptr is %s\n", runner);
	

	return 0;
}