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
	dlist_iter_t ctest = NULL;
	dlist_iter_t dtest = NULL;
	dlist_iter_t etest = NULL;

	void *ptr = NULL;
	
	int num = 666;
	int another_num = 26;
	size_t t = 111;

	printf("\n\t-------------------------Test 1--------------------------------\n\n");
	test = DListCreate();
	assert(NULL != test);
	
	(1 == DListIsEmpty(test)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");
	atest = DListBegin(test);
	printf("size is %ld\n",DListSize(test));
	

	printf("\n\t---------------inserting & printing nodes-------------------------\n");
	btest = DListInsert(atest, &num);
	ptr = DListGetData(btest);
	printf("btest is %d\n",*(int*)ptr);
	printf("size is %ld\n",DListSize(test));
	atest = DListInsert(btest, &another_num);

	ptr = DListGetData(atest);
	printf("atest is %d\n",*(int*)ptr);
	printf("size is %ld\n",DListSize(test));


	printf("\n\t----------------asserting inserted nodes arent equal---------\n");
	assert(DListIsEqual(atest,btest) == 0);
	(1 == DListIsEmpty(test)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");

	
	printf("\n\t-------------------------removing nodes-------------------------\n");
	
	ctest = DListRemove(atest);
	ptr = DListGetData(ctest);
	printf("removed atest node, remaining node val is %d\n",*(int*)ptr);
	printf("post removal size is %ld\n",DListSize(test));
	printf("\ntrying to remove End or Begin:\n");
	DListRemove(DListEnd(test));
	printf("size is %ld\n",DListSize(test));
	printf("\n\t----------------pushing nodes Front--------------------------------\n");
	dtest = DListPushFront(test, &t);
	printf("size is %ld\n",DListSize(test));
	ptr = DListGetData(dtest);
	
	printf("pushed node to front, value is %ld\n",*(size_t*)ptr);
	printf("\n\t---------------------Pop Front-----------------------------\n");
	
	ptr = DListPopFront(test);
	printf("popped front, value is %ld\n",*(size_t *)ptr);
	printf("size is now %ld\n",DListSize(test));
	printf("\n\t---------------inserted 2------------------------------------------\n");
	
	etest = DListInsert(dtest,&t);
	etest = DListInsert(etest,&num);
	printf("size is now %ld\n",DListSize(test));
	printf("\n\t------------------------------Pop Back-----------------------------\n");
	ptr = DListPopBack(test);
	printf("popped back, value is %d\n",*(int *)ptr);
	printf("size is now %ld\n",DListSize(test));
	/*dtest = DListPushBack(test, &num);
	ptr = DListGetData(dtest);
	printf("dtest is %d\n",*(int*)ptr);
	printf("size is %ld\n",DListSize(test));
	*/
	DListDestroy(test);

}