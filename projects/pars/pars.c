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
#include <string.h> /* strchr */

#include "pars.h" /* header*/

#define BADOP ('~')	

static int IsOperator(char op);


static const char operators[] = {'{','[','(','^','*','/','+','-',')',']','}'};



int ParseNum(const char *str, char **next_ptr, double *result)
{
	assert(NULL != str);

	*result = strtod(str,next_ptr);

	return (str != *next_ptr);
}


char ParseChar(const char *str, char **str_after_parse)
{
	char result = BADOP;
	assert(NULL != str);

	*str_after_parse = (char *)(str);

	while(isspace(**str_after_parse))
	{
		++(*str_after_parse);
	}
	
	if (IsOperator(**str_after_parse))
	{
		result = **str_after_parse;
		++(*str_after_parse);
	}
	
	return result;
}


static int IsOperator(char op)
{
	return (strchr(operators, op) != NULL);
}


/*
char ParseChar(const char *str, char **str_after_parse)
{
	char result = '@';
	assert(NULL != str);

	
	result = *str;
	
	
	*str_after_parse = (char *)(str + 1);
	

	return result;
	
}
*/