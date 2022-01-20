#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "pars.h"

static void TestParseNum();
static void TestParseChar();
int main(void)
{
	/*
	char *runner  = NULL;
	char *str = "12.5+5";
	
	double result = 0.0;
	printf("int is %d\n",ParseNum(str,&runner,&result));
	printf("parsed is: %f\n", result);
	printf("org string is %s\n", str);
	printf("rest ptr is %s\n", runner);
	printf("char %c parsed\n", ParseChar(runner, &runner));
	printf("rest ptr is %s\n", runner);
	*/
	TestParseNum();
	TestParseChar();
	return 0;
}

static void TestParseNum()
{
	char *runner  = NULL;
	char *str = "12.5+5";
	
	double result = 0.0;
	printf("Original string is %s\n", str);
	(1 == ParseNum(str,&runner,&result)) ? printf("Parsed Num!\n"): printf("didn't ParseNum\n");
	
	printf("parsed number is: %f\n", result);
	printf("remaining string is %s\n", runner);
}

static void TestParseChar()
{
	char *runner  = NULL;
	char *str = "165.88+54654.8";
	double result = 0.0;

	ParseNum(str,&runner,&result);
	printf("parsed number is: %f\n", result);
	printf("char %c parsed\n", ParseChar(runner, &runner));
	ParseNum(runner,&runner,&result);
	printf("parsed another num is: %f\n", result);

}