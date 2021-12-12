#include <stdio.h> /* standard lib, printf*/
#include <stdlib.h> /* dynamic memory allocation*/

#include "ptr_1.h"


int main(void)
{
	int *test = NULL;
	size_t *ptr1 = NULL, *ptr2 = NULL;
	size_t s_t1 = 0,s_t2 = 0;
	
	int array[] = {1,3,5,7,9,11};
	s_t1 = sizeof(array);
	s_t2 = sizeof(array[0]);
	
	ptr1 = &s_t1;
	ptr2 = &s_t2;
	
	
	

	printf("size is %ld\n",(s_t1/s_t2));
	test=CopyArray((s_t1/s_t2),array);
	printf("\ntest[1]is %d\n",*(test + 1));
	printf("\ntest[2]is %d\n",*(test + 2));
	
	printf("\ftest pointer was freed and nulled so dont try to access it!");
	  free(test);
	  test = NULL;


	printf("size in bytes of size_t1 is %lu, size_t2 is %lu, \n",s_t1,s_t2);
	  SwapSizeT(&s_t1, &s_t2);
	printf("post swap: size_t1 is %lu and size_t2 is %lu\n",s_t1,s_t2);


	printf("\ns_t1 value is %lu\n its ptr1 adrs is %p\n",s_t1,(void*)ptr1);
	printf("\ns_t2 value is %lu\n its ptr2 adrs is %p\n",s_t2,(void*)ptr2);
	   SwapPtrSize_t(&ptr1, &ptr2);
	printf("\npost pointer swap: s_t1 value is %lu\n its ptr1 adrs is %p\n",s_t1,(void*)ptr1);
	printf("\npost pointer swap: s_t2 value is %lu\n its ptr2 adrs is %p\n",s_t2,(void*)ptr2);

return 0;
}
	
