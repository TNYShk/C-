#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */

#include "sll.h"



int MatchFloat(void *data, void *param);
int AddDecimal(void *data, void *param);
void TestOne();
void TestTwo();



int main(void)
{

	TestOne();
	TestTwo();
	return 0;
}





void TestOne()
{
	void *float_ptr = NULL;
	float f = 3.14;
	float ff = 1.618;
	float fff = 6.66;
	slist_t *twinky = SListCreate();
	slist_iter_t start = NULL;
	slist_iter_t second = NULL;
	slist_iter_t third = NULL;
	slist_iter_t end = NULL;
	slist_iter_t find = NULL;

	match_func_t MatchTest = MatchFloat;



	assert(NULL != twinky);
	assert(SListIsEmpty(twinky));
	printf("\n\t----------------Test 1------------------\n");
	printf("\n\t********************new list and inserting nodes******************\n\n");
	start = SListBegin(twinky);
	end = SListEnd(twinky);

	assert(SListIsEqual(start, end) == 1);

	second = SListInsertBefore(end,&f);

	float_ptr = SListGetData(second);
	printf("inserted Before dummy, 1st value is %f\n",*(float *)float_ptr);
	printf("\n\t********************Asserting Inserted******************\n");
	assert(*(float*)float_ptr == f);
	assert(!SListIsEmpty(twinky));
	assert (1 == SListCount(twinky));

	third = SListInsertAfter(second, &ff);
	assert (2 == SListCount(twinky));
	float_ptr = SListGetData(third);
	printf("inserted After first, 2nd value is %f\n",*(float *)float_ptr);
	assert(*(float*)float_ptr == ff);
	
	assert(SListIsEqual(start, second) == 1);
	assert(SListIsEqual(third, end) == 0);

	f = 66.6;
	start = SListInsertBefore(third, &f);
	assert(SListIsEqual(third, start) == 1);
	float_ptr = SListGetData(start);
	printf("inserted Before 2nd,returning the inserted node, value is %.2f\n",*(float *)float_ptr);
	assert (3 == SListCount(twinky));

	assert(SListIsEqual(SListBegin(twinky), second) == 1);

	printf("\n\t********************Asserting Find Func******************\n");
	find = SListFind(SListBegin(twinky),SListEnd(twinky),MatchTest, &ff);
	(NULL == find)? printf("%.2f NOT in list\n",fff): printf("%f found it!\n",ff);
	find = SListFind(SListBegin(twinky),SListEnd(twinky),MatchTest, &fff);
	(NULL == find)? printf("%.2f not found in list\n",fff): printf("found it!\n");

	printf("\n\t*************************removing node***********************\n");
	float_ptr = SListGetData(third);
	printf("third the value is %f\n",*(float *)float_ptr);
	find = SListRemove(third);
	assert (2 == SListCount(twinky));
	float_ptr = SListGetData(find);
	printf("post removal of third, returning the next in line node value is %f\n",*(float *)float_ptr);

	SListDestroy(twinky);

}

void TestTwo()
{
	void *int_ptr = NULL;
	void *int_kptr = NULL;
	int t = 6;
	int tt = 66;
	int ttt = 666;
	slist_t *twinky = SListCreate();
	slist_t *kika = SListCreate();
	slist_iter_t start = NULL;
	slist_iter_t second = NULL;
	slist_iter_t third = NULL;
	slist_iter_t append = NULL;

	slist_iter_t k_start = NULL;
	slist_iter_t k_second = NULL;
	slist_iter_t k_end = NULL;
	slist_iter_t k_append = NULL;

	action_func_t AddSome = AddDecimal;

	assert(NULL != twinky);
	assert(NULL != kika);

	printf("\n\t----------------Test 2------------------\n");
	assert(SListIsEmpty(twinky));
	assert(SListIsEmpty(kika));
	printf("\n\t***************new lists inserting same value to diff lists*************\n\n");
	start = SListBegin(twinky);
	k_start = SListBegin(kika);

	second = SListInsertBefore(start, &t);
	int_ptr = SListGetData(second);
	printf("inserted 1st value to List1, value is %d\n",*(int *)int_ptr);
	
	k_second = SListInsertBefore(k_start, &t);
	int_kptr = SListGetData(k_second);
	printf("inserted 1st value to List2, = value is %d\n",*(int *)int_kptr);
	printf("\n\t******************** Asserting Inserted ******************\n");
	assert(second != k_second);
	printf("\n\t******************** Adding nodes ******************\n");
	third = SListInsertBefore(second, &ttt);
	int_ptr = SListGetData(third);
	printf("inserted 2st value to List1, Before first = value is %d\n",*(int *)int_ptr);

	k_end = SListInsertAfter(k_second, &tt);
	int_kptr = SListGetData(k_end);
	printf("inserted 2st value to List2, After first = value is %d\n",*(int *)int_kptr);

	printf("num of elements in List1 is %ld\n",SListCount(twinky));
	printf("num of elements in List2 is %ld\n",SListCount(kika));
	

	printf("\n\t******************** Testing Add Func ******************\n");
	int_kptr = SListGetData(k_start);
	printf("Pre add List2 1st node value is %d\n",*(int *)int_kptr);

	int_kptr = SListGetData(k_end);
	printf("Pre add List2 2st node value is %d\n",*(int *)int_kptr);
	SListForEach(SListBegin(kika), SListEnd(kika),AddSome, &t);

	int_kptr = SListGetData(k_start);
	printf("POST Add Func to List2, 1st node value is %d\n",*(int *)int_kptr);

	int_kptr = SListGetData(k_end);
	printf("POST Add Func to List2, 2st node value is %d\n",*(int *)int_kptr);

	printf("\n\t******************** Append List1 into List2 ******************\n");

	SlistAppend(kika, twinky);
	printf("\npost append number of nodes List2: %lu\n",SListCount(kika));
	printf("\npost append number of nodes List1: %lu\n",SListCount(twinky));

	printf("\n\t************************* Adding nodes to List1 ***********************\n");
	append = SListBegin(twinky);
	t = 26;
	append = SListInsertBefore(append,&t);
	int_ptr = SListGetData(append);
	printf("inserted node to List1, its value  %d\n",*(int *)int_ptr);
	printf("\nPost Append and insertion into List1 count is: %lu\n",SListCount(twinky));
	assert(SListCount(kika) != SListCount(twinky));
	printf("\nPost Append number of nodes List2: %lu\n",SListCount(kika));
	printf("\n\t************************* Adding nodes to List2 ***********************\n");
	k_append = SListInsertBefore(k_end, &t);
	int_kptr = SListGetData(k_append);
	printf("POST Append, adding node to List2, its value is %d\n",*(int *)int_kptr);
	printf("\nnumber of nodes List2, post add: %lu\n",SListCount(kika));
	printf("\nnumber of nodes in List1:  %lu\n",SListCount(twinky));

	printf("\n\t********************** Remove node from List2 ***********************\n");
	k_append = SListRemove(k_end);
	printf("\nnumber of nodes List2, post remove: %lu\n",SListCount(kika));

	SListDestroy(twinky);
	SListDestroy(kika);

}




int MatchFloat(void *data, void *param)
{
    return (*(float *)data == *(float *)param);
}


int AddDecimal(void *data, void *param)
{
    *(int *)data = *(int *)data + *(int *)param;

    return *(int *)data;
}
