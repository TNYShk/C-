#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "sll.h"

int main()
{
	void *ptr = NULL;
	slist_t *twinky = SListCreate();
	
	slist_iter_t node = twinky->head;
	int x = 5;
	ptr = &x;
	
	
	printf("size is %ld\n", sizeof(twinky));
	SListInsertAfter(node, ptr);
	SListDestroy(twinky);

	return 0;
}


