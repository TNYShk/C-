
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "pars.h"

int ParseNum(const char *str, char **next_ptr, double *result)
{
	assert(NULL != str);

	*result = strtod(str,next_ptr);

	return (str != *next_ptr);
}


char ParseChar(const char *str, char **str_after_parse)
{
	char result = '@';
	assert(NULL != str);
	result = *str;
	
	/*assert(!isalnum(result));*/
	*str_after_parse = (char *)(str + 1);
	

	return result;
	
}
