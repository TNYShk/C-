#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include "dll.h"

#define PRINT_NODE(node) (printf("node at address %p has int %d, prev is %p, next is %p\n", \
        (void *)node, *(int *)DListGetData(node), (void *)DListPrev(node), (void *)DListNext(node)));



void TestOne();
void TestTwo();
int MatchInt(const void *data, void *param);
void TestFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *data);
int AddInt(void *data, void *param);



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
	TestTwo();


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

	
	
	int num = 666;
	int another_num = 26;
	size_t t = 111;

	printf("\n\t***********************-Test-1-*********************************\n\n");
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
	
	printf("\n\t---------------------pushing nodes Front--------------------------------\n");
	dtest = DListPushFront(test, &t);
	printf("size is %ld\n",DListSize(test));
	
	PrintDListForward(test);

	printf("\n\t---------------------------Pop Front-----------------------------------\n");
	DListPopFront(test);
	
	printf("size is now %ld\n",DListSize(test));
	PrintDListForward(test);

	printf("\n\t------------------------inserted 3------------------------------------------\n");
	etest = DListInsert(dtest,&t);
	ftest = DListInsert(etest,&num);
	ctest = DListInsert(ftest,&another_num);
	PrintDListForward(test);
	printf("inserted before end, is it equal? %d\n",(DListIsEqual(DListPrev(DListEnd(test)),dtest)));
	

	DListDestroy(test);

}

void TestTwo()
{
	dlist_t *test1 = NULL;
	dlist_t *test2 = NULL;
	dlist_t *multifind_test = NULL;
	dlist_iter_t tatest = NULL;
	dlist_iter_t tbtest = NULL;
	dlist_iter_t tctest = NULL;

	size_t one = 1;
	size_t wto = 2;
	size_t three = 3;
	size_t hund = 100;
	printf("\n\t*************************-Test 2-*********************************\n\n");
	
	test1 = DListCreate();
	test2 = DListCreate();
	assert(NULL != test2);
	
	PrintDListForward(test2);

	(1 == DListIsEmpty(test2)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");

	printf("\n\t----------------pushing nodes 2 Front--------------------------------\n");

	tatest = DListBegin(test2);
	tatest = DListPushFront(test2, &one);
	tbtest = DListPushFront(test2, &wto);
	PrintDListForward(test2);

	printf("\n\t---------------------Pop Front-----------------------------\n");
	DListPopFront(test2);
	PrintDListForward(test2);

	printf("\n\t---------------------insert 5-----------------------------\n");
	tctest = DListInsert(tbtest,&three);
	PrintDListForward(test2);
	DListInsert(tctest,&wto);
	DListInsert(tctest,&one);
	DListPushFront(test2, &three);
	printf("\n\t----------------------------list1 -----------------------------\n");
	PrintDListForward(test2);

	printf("\n\t---------------------------list2 -----------------------------\n");
	DListPushFront(test1, &one);
	DListPushFront(test1, &one);
	DListPushFront(test1, &one);
	PrintDListForward(test1);
	printf("\n\t---------------------splice remove from one add to other ------------------------\n");
	DListSplice(DListBegin(test2), DListNext(DListBegin(test1)), DListEnd(test1));
	printf("\n\t------------------------post splice list1 -----------------------------\n");
	PrintDListForward(test2);
	printf("\n\t-----------------------post splice list2 -----------------------------\n");

	PrintDListForward(test1);
	printf("\n\t-----------------------add element to list2 -----------------------------\n");
	DListPushFront(test1, &one);
	PrintDListForward(test1);
	printf("\n-----------------------------Find function test:--------------------------:\n\n");
	
	printf("Trying to find number 100 in main list:\n");
	TestFind(DListBegin(test2), DListEnd(test2), MatchInt, &hund);
	printf("asserting if 1 is in list1 (it is)\n");
	assert(DListFind(DListBegin(test2), DListEnd(test2), MatchInt, &one) != NULL);
	PrintDListForward(test2);
	printf("\n---------------------------MultiFind into new list--------------------------:\n\n");
	
	multifind_test = DListCreate();
	DListMultiFind(DListBegin(test2), DListEnd(test2), MatchInt, &one, multifind_test);
	PrintDListForward(multifind_test);

	printf("\n---------------------------For Each test--adding 3 to each element------------------------:\n\n");
	printf("\n---------before-----------:\n");
	PrintDListForward(test1);
	DListForEach(DListBegin(test1), DListEnd(test1),AddInt, &one);
	printf("\n---------after-----------:\n");
	PrintDListForward(test1);


	DListDestroy(multifind_test);
	DListDestroy(test1);
	DListDestroy(test2);
}






void TestFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *data)
{
	if (DListFind(from, to, is_match, data))
	{
		printf("Found it!\n");
	}
	else
	{
		printf("Not Here!\n");
	}
}
