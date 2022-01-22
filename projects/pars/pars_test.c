/**********************************************
 * Parser - Test File         			      *
 * Developer: Tanya			                  *
 *          Jan 20, 2022                      *
 *                                            *
 * Reviewer:  		  	                      *
 **********************************************/
#include <stdio.h> /* printf */

#include "pars.h" /* program header*/

#define BADOP ('#')	


static void TestParseNum();
static void TestParseChar();
static void CombineParse();
static void NewTest();

int main(void)
{
	
	TestParseNum();
	TestParseChar();

	CombineParse();
	NewTest();
	return 0;
}


static void TestParseNum()
{
	char *runner  = NULL;
	char *str = "12.5+5";
	char *b_num = "*56";
	double result = 0.0;

	printf("\n********Test ParseNum***********\nOriginal string is %s\n", str);
	(1 == ParseNum(str,&runner,&result)) ? printf("Parsed Num!\n"): printf("didn't ParseNum\n");
	
	printf("parsed number is: %f\n", result);
	printf("remaining string is %s\n", runner);
	
	printf("\n---------test2--------\n");
	printf("Original string is %s\n", b_num);
	(1 == ParseNum(b_num,&runner,&result)) ? printf("Parsed Num!\n"): printf("didn't ParseNum\n");
	printf("parsed number is: %f\n", result);
	printf("remaining string is %s\n", runner);
}

static void TestParseChar()
{
	char *runner  = NULL;
	char *str = "165.88 +123456789.123456789";
	double result = 0.0;
	printf("\n********Test ParseChar***********\nOriginal string is %s\n", str);
	ParseNum(str,&runner,&result);
	printf("parsed number is: %.4f\n", result);

	printf("char %c parsed\n", ParseChar(runner, &runner));
	ParseNum(runner,&runner,&result);
	printf("parsed another num is: %.4f\n", result);
}

static void CombineParse()
{
	char *runner  = NULL;
	char *str = "-165.88 + (123456789.123456789* 550)- 15";
	double result = 0.0;
	char ch = ' ';
	
	printf("\n\t**************Combined Test************\nOriginal string is %s\n", str);
	
	printf("Parse it down: \n");
	ParseNum(str,&runner,&result);
	printf("%f ,",result);

	while ((*runner != '\0') && (ch != BADOP))
	{
		ch = ParseChar(runner, &runner);
		printf(" %c ", ch);
		ParseNum(runner,&runner,&result);
		if(result != 0)
			printf(", %.4f ,",result);
			
			
	}
		printf("\n");
}


static void NewTest()
{
	char *runner  = NULL;
	char *str = "((-165.88) + (123456789.123456789* 550)- 15)";
	double result = 0.0;
	char ch = ' ';
	
	printf("\n\t*****Combined Test2*****\nOriginal string is %s\n", str);
	printf("Parse it down: \n");
	
	if(ParseNum(str,&runner,&result) == 0)
	{
		ch = ParseChar(runner, &runner);
		printf(" %c ,", ch);
	}

	else
	{
		ParseNum(str,&runner,&result);
		printf("%f ,",result);
	}
	
	while ((*runner != '\0') && (ch != BADOP))
	{
		
		ch = ParseChar(runner, &runner);
		printf(" %c ,", ch);
		ParseNum(runner,&runner,&result);
		if(result != 0)
			printf(" %f ,",result);
			
			
	}
		printf("\n");

}