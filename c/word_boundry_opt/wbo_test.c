#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#include "wbo.h"

typedef struct test{
	char str[30];
	char srr[30];
}test_t;

static test_t ar[3]={
	{"Hell123456789","MemMove"},
	{"Hello","source123"},
	{"Google ", " without"}
};

int main()
{

	
	MemMove(ar[0].str, ar[0].srr,7);
	MemSet(ar[1].str, 'A',2);
	MemCpy(ar[2].str+6, ar[2].srr,70);
	printf("%s\n",ar[0].str);
	printf("%s\n",ar[1].str);
	printf("%s\n",ar[2].str);

	

	
	
	return 0;
}


