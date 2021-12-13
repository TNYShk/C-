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
	
	size_t x = 5;
	ptr = &x;
	Istart = SListBegin(twinky);
	printf("size is %ld\n", sizeof(twinky));
	
	
	Istart = SListInsertBefore(Istart, ptr);
	ptr = SListGetData(Istart);
	printf("ptr is %ld\n",*(size_t*)ptr);
	
	x = 500;
	ptr = &x;
	testinsert = SListInsertAfter(Istart,ptr);
	
	ptr = SListGetData(testinsert);
	printf("SListInsertAfter start value is %ld\n",*(size_t*)ptr);
	
	printf("is it empty? %d\n", SListIsEmpty(twinky));

	printf("number of nodes is %lu\n",SListCount(twinky));
	SListDestroy(twinky);

	return 0;
}


