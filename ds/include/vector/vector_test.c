#include <stdlib.h> /* size_t */
#include <stdio.h> /*         */
#include <string.h>
#include <assert.h>
#include "dynamic_vector.h"

int main(void)
{
	size_t test,test2;
	void *ptr;
	void *ptr2;
	vector_t *vitor = NULL;
	vitor = VectorCreate(sizeof(size_t), 3);
	assert (NULL != vitor); 
	
	printf("\ninitialized capacity: %ld\n",VectorCapacity(vitor));
	printf("\t\t-------------Adding 3 elements to Vector---------------\n");
	test2 = 5;

	test = VectorPushBack(vitor,&test2);
	printf("element pushed into vector's back, zero for success: %ld\n", test);
	test2 = 6;
	
	test = VectorPushBack(vitor,&test2);
	printf("element pushed into vector's back, zero for success: %ld\n", test);
	printf("\ncurrent taken elements %ld\n",VectorSize(vitor));
	test2 = 7;
	test = VectorPushBack(vitor,&test2);
	printf("element pushed into vector's back, zero for success: %ld\n", test);
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	printf("\ncapacity is now %ld\n",VectorCapacity(vitor));
	
	
	printf("\t\t-------------printing vectors values---------------\n");
	ptr = VectorGetAccessToElement(vitor,3);
	printf("\n\telement3 is: %ld\n", *(size_t*)ptr);
	ptr2 = VectorGetAccessToElement(vitor,1);
	printf("\n\telement1: %ld\n", *(size_t*)ptr2);
	ptr2 = VectorGetAccessToElement(vitor,2);
	printf("\n\telement2: %ld\n", *(size_t*)ptr2);

	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));

	printf("\t\t-------------Pop Pop-------------------------------\n");
	VectorPopBack(vitor);
	
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	VectorPopBack(vitor);
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	
	
	printf("\n\tcapacity is now %ld\n",VectorCapacity(vitor));
	VectorDestroy(vitor);

return 0;

}