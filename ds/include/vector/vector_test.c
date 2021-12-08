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
	vector_t *victor = NULL;
	victor = VectorCreate(sizeof(size_t), 3);
	assert (NULL != victor); 
	test2 = 5;

	test = VectorPushBack(victor,&test2);
	printf("element pushed into vector's back, size is %ld\n", test);
	test2 = 6;
	
	test = VectorPushBack(victor,&test2);
	printf("element pushed into vector's back, size is %ld\n", test);
	printf("\n\tcurrent size is %ld\n",VectorSize(victor));
	test2 = 7;
	test = VectorPushBack(victor,&test2);
	printf("element pushed into vector's back, size is %ld\n", test);
	
	printf("\n\tcapacity is %ld\n",VectorCapacity(victor));
	
	
	printf("\t\t-----------printing vectors values---------------\n");
	ptr = VectorGetAccessToElement(victor,3);
	printf("\nelement3 is: %ld\n", *(size_t*)ptr);
	ptr2 = VectorGetAccessToElement(victor,1);
	printf("element1: %ld\n", *(size_t*)ptr2);
	ptr2 = VectorGetAccessToElement(victor,2);
	printf("element2: %ld\n", *(size_t*)ptr2);

	printf("\ncurrent taken elements: %ld\n",VectorSize(victor));
	printf("\t\t-----------Pop Pop-------------------------------\n");
	VectorPopBack(victor);
	printf("\npost pop element3 is: %ld\n", *(size_t*)ptr);
	printf("\ncurrent taken elements: %ld\n",VectorSize(victor));
	VectorPopBack(victor);
	printf("\ncurrent taken elements: %ld\n",VectorSize(victor));
	printf("\ncapacity is %ld\n",VectorCapacity(victor));
	VectorDestroy(victor);

return 0;

}