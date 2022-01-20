/************************************
 * Parser - Source File         	*
 * Developer: Tanya			        *
 *          Jan 20, 2022            *
 *                                  *
 * Reviewer:  		  	            *
 ************************************/
#include <stdlib.h> /* strtod*/
#include <assert.h> /* assert */
#include <ctype.h> /* isspace, isdigit*/

#include "pars.h" /* header*/

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
