#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */

#include "dll.h"

#define PRINT_NODE(node) (printf("node at address %p has int %d, prev is %p, next is %p\n", \
        (void *)node, *(int *)DListGetData(node), (void *)DListPrev(node), (void *)DListNext(node)));

/***********************************
 * Doubly Linked List WS		   *
 *  Proud Surviver           	   *
 * by Tanya					       *
 *   Dec 20				           *
 *                                 *
 * Reviewer: Erez                  *
 ***********************************/





void TestOne();
void TestTwo();

int MatchNum(const void *data, const void *param);
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
	dlist_iter_t dtest = NULL;
	
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
	

	printf("\n\t---------------Insert nodes to list-------------------------\n");
	btest = DListInsert(atest, &num);
	PrintDListForward(test);
	
	printf("size is %ld\n",DListSize(test));
	atest = DListInsert(btest, &another_num);
	PrintDListForward(test);
	
	printf("\n\t----------------Asserting inserted nodes arent equal---------\n");
	assert(DListIsEqual(atest,btest) == 0);
	(1 == DListIsEmpty(test)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");

	
	printf("\n\t-------------------------removing nodes-------------------------\n");
	
	DListRemove(atest);
	printf("post removal size is %ld\n",DListSize(test));
	PrintDListForward(test);
	DListRemove(DListPrev(DListEnd(test)));

	printf("size is %ld\n",DListSize(test));
	PrintDListForward(test);
	
	printf("\n\t---------------------pushing nodes Front--------------------------------\n");
	dtest = DListPushFront(test, &t);
	DListPushFront(test, &another_num);
	printf("size is %ld\n",DListSize(test));
	
	PrintDListForward(test);

	printf("\n\t---------------------------Pop Front-----------------------------------\n");
	DListPopFront(test);
	PrintDListForward(test);
	

	printf("\n\t------------------------Push Back 3 nodes ---------------------------------\n");
	
	DListPushBack(test, &t);
	DListPushBack(test, &num);
	dtest = DListPushBack(test, &another_num);
	PrintDListForward(test);
	printf("\n\t------------------------Is Equal?------------------------------------------\n");
	printf("Pushed to End , is it equal? %d\n",(DListIsEqual(DListPrev(DListEnd(test)),dtest)));
	
	DListDestroy(test);
}


void TestTwo()
{
	dlist_t *test1 = NULL;
	dlist_t *test2 = NULL;
	dlist_t *multifind_test = NULL;
	dlist_iter_t tctest = NULL;
	int answer = -5;
	size_t one = 1;
	size_t wto = 2;
	size_t three = 3;
	size_t hund = 100;
	printf("\n\n\n\t*************************-Test 2-*********************************\n\n");
	
	test1 = DListCreate();
	test2 = DListCreate();
	assert(NULL != test2);
	
	PrintDListForward(test2);

	(1 == DListIsEmpty(test2)) ? printf("Empty dlist\n") : printf("NOT Empty dlist\n");

	printf("\n\t----------------Pushing nodesFront & Back--------------------------------\n");

	tctest = DListBegin(test2);
	DListPushFront(test2, &one);
	tctest = DListPushBack(test2, &wto);
	PrintDListForward(test2);

	printf("\n\t-----------------------------Pop Front-----------------------------------\n");
	DListPopFront(test2);
	PrintDListForward(test2);

	printf("\n\t-------------------------Insert 2 nodes----------------------------------\n");
	DListInsert(tctest,&wto);
	DListInsert(tctest,&one);
	PrintDListForward(test2);

	printf("\n\t----------------------Push num 3 Back & Front----------------------------\n");
	DListPushBack(test2, &three);
	DListPushFront(test2, &three);
	
	printf("\n\t----------------------------list1 -----------------------------\n");
	PrintDListForward(test2);

	printf("\n\t-------------------------New list2, pushing to front 3X1 -----------------------------\n");
	DListPushFront(test1, &one);
	DListPushFront(test1, &one);
	DListPushFront(test1, &one);
	PrintDListForward(test1);
	
	printf("\n\t---------------------SPLICE TEST remove from list2, add to list1 ------------------------\n");
	DListSplice(DListBegin(test2), DListNext(DListBegin(test1)), DListEnd(test1));

	printf("\n\t------------------------Post Splice list1 -----------------------------\n");
	PrintDListForward(test2);
	printf("\n\t-----------------------Post Splice list2 -----------------------------\n");

	PrintDListForward(test1);

	printf("\n\t------------------------Pop Back X3 list1 -----------------------------\n");
	DListPopBack(test2);
	DListPopBack(test2);
	DListPopBack(test2);
	PrintDListForward(test2);

	
	printf("\n\t-----------------------Push to Front in list2 -----------------------------\n");
	DListPushFront(test1, &one);
	PrintDListForward(test1);
	
	printf("\n\n\t-----------------------------Find function test:--------------------------\n");
	
	printf("Trying to find number 100 in main list:\n");
	TestFind(DListBegin(test2), DListEnd(test2), MatchNum, &hund);
	
	printf("Asserting if 1 is in list1 (it is, here is the list)\n");
	assert(DListFind(DListBegin(test2), DListEnd(test2), MatchNum, &one) != NULL);
	PrintDListForward(test2);
	
	printf("\n\n\t---------------------------MultiFind into new list3--------------------------\n");
	
	multifind_test = DListCreate();

	answer = DListMultiFind(DListBegin(test2), DListEnd(test2), MatchNum, &one, multifind_test);
	(answer == 0)? printf("Multifound! and inserted to new list!, its size is %ld\n",DListSize(multifind_test)): printf("Multifind didnt find \n");
	DListDestroy(multifind_test);
	

	printf("\n\n\t---------------------------For Each test--adding num to each element------------------------\n");
	printf("\n---------Pre For Each-----------:\n");
	PrintDListForward(test1);
	DListForEach(DListBegin(test1), DListEnd(test1),AddInt, &one);
	printf("\n---------Post For Each-----------:\n");
	PrintDListForward(test1);


	
	
	DListDestroy(test1);
	DListDestroy(test2);
}


void TestFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *data)
{
	if (DListFind(from, to, is_match, data) != to )
	{
		printf("Found it!\n");
	}
	else
	{
		printf("Not Here!\n");
	}
}
