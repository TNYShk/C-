
#include <stdio.h>
#include <string.h>
#include <stdlib.h>




int ParserNum(const char *str, char *next_ptr, double *result)
{
	assert(NULL != str);
	*result = strtod(str,&next_ptr);

	return (str != next_ptr);
}


int ParserChar(const char *str, char *next_ptr, char *result)
{
	assert(NULL != str);
	*result = str[0];
	next_ptr = ++str;
	
	return (!isdigit(result));

}
