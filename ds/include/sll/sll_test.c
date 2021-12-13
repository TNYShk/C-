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
	slist_iter_t end = NULL;
	size_t x = 5;
	ptr = &x;
	Istart = SListBegin(twinky);
	
	
	
	Istart = SListInsertBefore(Istart, ptr);
	ptr = SListGetData(Istart);
	printf("\ninserted first value(before dummy)! value is %ld\n",*(size_t*)ptr);
	
	x = 500;
	ptr = &x;
	testinsert = SListInsertAfter(Istart,ptr);
	
	ptr = SListGetData(testinsert);
	printf("SListInsertAfter start value, value is %ld\n",*(size_t*)ptr);
	
	printf("is sll empty? (zero for NO) %d\n", SListIsEmpty(twinky));

	printf("number of nodes: %lu\n",SListCount(twinky));
	end = SListEnd(twinky);
	ptr = SListGetData(end);
	printf("\nvalue of last element (dummy) is garbage  %ld\n",*(size_t*)ptr);

	SListDestroy(twinky);

	return 0;
}


