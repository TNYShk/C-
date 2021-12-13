#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "sll.h"

int main()
{
	slist_t *twinky = SListCreate();
	

	printf("size is %ld\n", sizeof(twinky));
	SListDestroy(twinky);


	return 0;
}


