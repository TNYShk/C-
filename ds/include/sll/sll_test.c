#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "sll.h"

int main()
{
	void *ptr = NULL;
	slist_t *twinky = SListCreate();
	slist_iter_t Istart = NULL;
	slist_iter_t testinsert = NULL;
	slist_iter_t testinsertb4 = NULL;
	slist_iter_t end = NULL;
	size_t x = 5;
	float f = 3.14;
	ptr = &x;
	Istart = SListBegin(twinky);
	
	
	printf("Created SLL fresh! Zero for empty: %d\n", SListIsEmpty(twinky));
	Istart = SListInsertBefore(Istart, ptr);
	ptr = SListGetData(Istart);
	printf("\ninserted first value(before dummy)! value is %ld\n",*(size_t*)ptr);
	
	x = 500;
	ptr = &x;
	testinsert = SListInsertAfter(Istart,ptr);
	
	ptr = SListGetData(testinsert);
	printf("SListInsertAfter start value, value is %ld\n",*(size_t*)ptr);
	
	printf("is sll empty? (zero for NO) %d\n", SListIsEmpty(twinky));

	printf("\tnumber of nodes: %lu\n",SListCount(twinky));
	end = SListEnd(twinky);
	printf("\n*************************removing nodes***********************\n");
	end = SListRemove(end);
	testinsert = SListRemove(testinsert);
	printf("\tnumber of nodes: %lu\n",SListCount(twinky));
	ptr = &f;
	printf("\n*************************Adding nodes***********************\n");
	testinsertb4 = SListInsertAfter(testinsert,ptr);
	ptr = SListGetData(testinsertb4);
	printf("SListInsertafter end value, value is %f\n",*(float *)ptr);
	f = 1.618;
	ptr = &f;
	testinsertb4 = SListInsertBefore(testinsert,ptr);
	ptr = SListGetData(testinsertb4);
	printf("SListInsertBefore end value, value is %f\n",*(float *)ptr);
	f = 1.99999;
	SListSetData(testinsertb4,(void*)&f);
	ptr = SListGetData(testinsertb4);
	printf("\nSetValue test, changed to %f\n",*(float *)ptr);
	printf("\tnumber of nodes: %lu\n",SListCount(twinky));


	SListDestroy(twinky);

	return 0;
}


