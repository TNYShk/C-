#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include "dll.h"

void TestOne();


int main (void)
{

	TestOne();


	return 0;
}


void TestOne(void)
{
	dlist_t *test = NULL;
	dlist_iter_t atest = NULL;
	dlist_iter_t btest = NULL;

	int num = 666;
	int another_num = 26;

	test = DListCreate();
	assert(NULL != test);
	printf("\n\t-------------------------Test 1--------------------------------\n\n");
	(1 == DListIsEmpty(test)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");

	atest = DListBegin(test);
	printf("size is %ld\n",DListSize(test));
	btest = DListInsert(atest, &num);
	printf("\n\t-------------------------inserting nodes-------------------------\n");
	printf("size is %ld\n",DListSize(test));
	atest = DListInsert(btest, &another_num);
	printf("size is %ld\n",DListSize(test));
	(1 == DListIsEmpty(test)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");

	
	DListDestroy(test);

}