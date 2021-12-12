#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memmove                      */
#include <assert.h>    /* assert                      */ 

#include "dynamic_vector.h"

int main(void)
{
	size_t test,test2;
	float f = 1.618;
	void *ptr = NULL;
	void *ptr2 = NULL;
	vector_t *vitor = NULL;
	vitor = VectorCreate(sizeof(size_t), 3);
	assert (NULL != vitor); 
	
	printf("\n\t\t---------------Initialized!--welcome Vitor!---------------\n");
	printf("\ninitialized capacity: %ld\n",VectorCapacity(vitor));
	printf("\t\t---------------Adding 3 elements to Vitor the vector---------------\n");
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
	
	
	printf("\t\t------------------Printing--element--values------------------\n");
	ptr = VectorGetAccessToElement(vitor,3);
	printf("\n\telement3 is: %ld\n", *(size_t*)ptr);
	ptr2 = VectorGetAccessToElement(vitor,1);
	printf("\n\telement1: %ld\n", *(size_t*)ptr2);
	ptr2 = VectorGetAccessToElement(vitor,2);
	printf("\n\telement2: %ld\n", *(size_t*)ptr2);
	

	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));

	printf("\t\t----------------------Pop--Pop----------------------------\n");
	VectorPopBack(vitor);
	
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	VectorPopBack(vitor);
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	
	
	printf("\n\tcapacity is now %ld\n",VectorCapacity(vitor));
	printf("\t\t-------------------Push-Push-------------------------------\n");
	test2 = 17;

	test = VectorPushBack(vitor,&test2);
	printf("element pushed into vector's back, zero for success: %ld\n", test);
	test2 = 18;
	
	test = VectorPushBack(vitor,&test2);
	printf("element pushed into vector's back, zero for success: %ld\n", test);
	printf("\ncurrent taken elements %ld\n",VectorSize(vitor));
	
	test = VectorPushBack(vitor,&f);
	ptr2 = VectorGetAccessToElement(vitor,4);
	
	printf("element pushed into vector's back, zero for success: %ld\n", test);
	
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	printf("\ncapacity is now %ld\n",VectorCapacity(vitor));
	
	printf("\t\t-----------------Printing--element--values---------------\n");
	ptr = VectorGetAccessToElement(vitor,3);
	printf("\n\telement3 is: %ld\n", *(size_t*)ptr);
	ptr2 = VectorGetAccessToElement(vitor,1);
	printf("\n\telement1: %ld\n", *(size_t*)ptr2);
	ptr2 = VectorGetAccessToElement(vitor,2);
	printf("\n\telement2: %ld\n", *(size_t*)ptr2);
	ptr2 = VectorGetAccessToElement(vitor,4);
	printf("\n\telement4: %f\n", *(float *)ptr2);


	
	printf("\t\t-------------------Push Push-------------------------------\n");
	test2 = 26;
	test = VectorPushBack(vitor,&test2);
	printf("\nelement pushed into vector's back, zero for success: %ld\n", test);
	ptr2 = VectorGetAccessToElement(vitor,5);
	printf("\n\tThe 5'th Element: %ld\n", *(size_t*)ptr2);
	test2 = 200;
	test = VectorPushBack(vitor,&test2);
	printf("element pushed into vector's back, zero for success: %ld\n", test);
	ptr2 = VectorGetAccessToElement(vitor,6);
	printf("\n\telement6: %ld\n", *(size_t*)ptr2);
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	printf("\ncapacity is now %ld\n",VectorCapacity(vitor));
	
	printf("\t\t----------------Pop--Pop--Pop-------------------------------\n");
	VectorPopBack(vitor);
	VectorPopBack(vitor);
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	VectorPopBack(vitor);
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	
	
	printf("\n\tcapacity is now %ld\n",VectorCapacity(vitor));
	printf("\t\t----------------Resize to 2-------------------------------\n");
	vitor = VectorReserve(vitor, 2);
	printf("\n\tcapacity is now %ld\n",VectorCapacity(vitor));
	printf("\t\t-------------------Push ----------------------------------\n");
	test2 = 26;
	test = VectorPushBack(vitor,&test2);
	printf("\nelement pushed into vector's back, zero for success: %ld\n", test);
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	test2 = 27;
	test = VectorPushBack(vitor,&test2);
	printf("\nelement pushed into vector's back, zero for success: %ld\n", test);
	printf("\ncurrent taken elements: %ld\n",VectorSize(vitor));
	test2 = 27;
	test = VectorPushBack(vitor,&test2);
	printf("\nelement pushed into vector's back, zero for success: %ld\n", test);
	printf("\n\tcapacity is now %ld\n",VectorCapacity(vitor));


	VectorDestroy(vitor);

return 0;

}