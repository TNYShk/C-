#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include "dll.h"

#define PRINT_NODE(node) (printf("node at address %p has int %d, prev is %p, next is %p\n", \
        (void *)node, *(int *)DListGetData(node), (void *)DListPrev(node), (void *)DListNext(node)));

void TestOne();


static void PrintDListForward(const dlist_t *dlist)
{
    
    dlist_iter_t runner = NULL;
    
    assert(NULL != dlist);
    
    runner = DListPrev(DListBegin(dlist));
    
    printf("\n-------List is:------\n");
    
    while (runner != NULL)
    {
        PRINT_NODE(runner);
        runner = DListNext(runner);
    }
    printf("Size of list is: %lu. List %s.\n", DListSize(dlist), DListIsEmpty(dlist) ? "is empty" : "is not empty");
}




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
	dlist_iter_t ftest = NULL;

	void *ptr = NULL;
	
	int num = 666;
	int another_num = 26;
	size_t t = 111;

	printf("\n\t-------------------------Test 1--------------------------------\n\n");
	test = DListCreate();
	assert(NULL != test);
	
	PrintDListForward(test);

	(1 == DListIsEmpty(test)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");
	atest = DListBegin(test);
	printf("size is %ld\n",DListSize(test));
	
	

	printf("\n\t---------------inserting & printing nodes-------------------------\n");
	btest = DListInsert(atest, &num);
	PrintDListForward(test);
	
	printf("size is %ld\n",DListSize(test));
	atest = DListInsert(btest, &another_num);
	PrintDListForward(test);
	
	printf("size is %ld\n",DListSize(test));


	printf("\n\t----------------asserting inserted nodes arent equal---------\n");
	assert(DListIsEqual(atest,btest) == 0);
	(1 == DListIsEmpty(test)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");

	
	printf("\n\t-------------------------removing nodes-------------------------\n");
	
	ctest = DListRemove(atest);
	
	
	printf("post removal size is %ld\n",DListSize(test));
	printf("\ntrying to remove End or Begin:\n");
	DListRemove(DListEnd(test));
	printf("size is %ld\n",DListSize(test));
	PrintDListForward(test);
	printf("\n\t----------------pushing nodes Front--------------------------------\n");
	dtest = DListPushFront(test, &t);
	printf("size is %ld\n",DListSize(test));
	ptr = DListGetData(dtest);
	PrintDListForward(test);
	printf("pushed node to front, value is %ld\n",*(size_t*)ptr);
	printf("\n\t---------------------Pop Front-----------------------------\n");
	ptr = DListPopFront(test);
	printf("popped front, value is %ld\n",*(size_t *)ptr);
	printf("size is now %ld\n",DListSize(test));
	PrintDListForward(test);
	printf("\n\t---------------inserted 2------------------------------------------\n");
	etest = DListInsert(dtest,&t);
	etest = DListInsert(etest,&num);
	PrintDListForward(test);
	printf("inserted before end, is it equal? %d\n",(DListIsEqual(DListPrev(DListEnd(test)),dtest)));
	PrintDListForward(test);
	


	DListDestroy(test);

}
