/**********************************************
 * Parser - Test File         			      *
 * Developer: Tanya			                  *
 *          Jan 20, 2022                      *
 *                                            *
 * Reviewer:  		  	                      *
 **********************************************/
#include <stdio.h> /* printf */

#include "pars.h" /* program header*/

static void TestParseNum();
static void TestParseChar();
static void CombineParse();

int main(void)
{
	
	TestParseNum();
	TestParseChar();

	CombineParse();
	return 0;
}


static void TestParseNum()
{
	char *runner  = NULL;
	char *str = "12.5+5";
	char *b_num = "*56";
	double result = 0.0;
	printf("Original string is %s\n", str);
	(1 == ParseNum(str,&runner,&result)) ? printf("Parsed Num!\n"): printf("didn't ParseNum\n");
	
	printf("parsed number is: %f\n", result);
	printf("remaining string is %s\n", runner);
	
	printf("test2\n");
	printf("Original string is %s\n", b_num);
	(1 == ParseNum(b_num,&runner,&result)) ? printf("Parsed Num!\n"): printf("didn't ParseNum\n");
	printf("parsed number is: %f\n", result);
	printf("remaining string is %s\n", runner);
}

static void TestParseChar()
{
	char *runner  = NULL;
	char *str = "165.88+123456789.123456789";
	double result = 0.0;
	printf("Original string is %s\n", str);
	ParseNum(str,&runner,&result);
	printf("parsed number is: %.4f\n", result);
	printf("char %c parsed\n", ParseChar(runner, &runner));
	ParseNum(runner,&runner,&result);
	printf("parsed another num is: %.4f\n", result);
}

static void CombineParse()
{
	char *runner  = NULL;
	char *str = "-165.88 + (123456789.123456789* -550)-15";
	double result = 0.0;
	char ch = '@';
	int flag = 1;

	printf("\n\tCombined Test\n");
	printf("Original string is %s\n", str);
	printf("Parse id down: \n");
	if(flag == ParseNum(str,&runner,&result))
	{
		printf("%f ,",result);

		while (*runner != '\0')
		{
			ch = ParseChar(runner, &runner);
			printf(" %c ", ch);
			flag = ParseNum(runner,&runner,&result);
			if(flag == 1)
			{
				printf(", %.4f ,",result);
			}
			
		}
		printf("\n");
	}
}