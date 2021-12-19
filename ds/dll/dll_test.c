#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include "dll.h"

void TestOne();


int main (void)
{

	dlist_t *test = NULL;
	test = DListCreate();
	assert(NULL != test);
	
	(1 == DListIsEmpty(test)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");

	DListDestroy(test);


	return 0;
}


void TestOne(void)
{

}