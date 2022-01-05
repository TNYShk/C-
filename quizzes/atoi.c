#include <stdlib.h> /* size_t  */
#include <assert.h> /* asserts */
#include <stdio.h> /* printf */
#include <ctype.h> /*isspace, isalnum, toupper, isdigit  */
#include <string.h>

#define ZERO ('0')
#define CAP_LETTER ('A')
#define DECIMAL (10)
#define CONVERT_NEG (-1)

int AtoI(const char *string);



int main(void)
{
	char *test = "6f0";

	printf("%s converted to int is %d\n", test,AtoI(test));
	printf("%c is %c\n", 'c', toupper('c'));
	
	return 0;
}

int AtoI(const char *string)
{
	int answer = 1;
	int sign = 1;

	assert(NULL != string);

	while(isspace(*string))
	{
		++string;
	}
	
	if (*string == '-')
	{
		sign = CONVERT_NEG;
		++string;
	}
	while (isalnum(*string))
	{
		if(isdigit(*string))
		{
			
			answer = (answer * DECIMAL) + *string - ZERO;
		}
		else
		{
			answer = (answer * DECIMAL) + toupper(*string) - CAP_LETTER + DECIMAL;
		}
		++string;
	}
	
	return sign * answer;
}
