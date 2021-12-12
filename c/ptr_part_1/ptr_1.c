#include <stdio.h>
#include <stdlib.h>

#include "ptr_1.h"



void SwapPtrSize_t(size_t **a,size_t **b)
{
	SwapSizeT((size_t *)a, (size_t *)b);
}


void Swap2Ints(int *num1, int *num2)
{
	int placeholder= *num1;
	*num1 = *num2;
	*num2 = placeholder;
}


int* CopyArray(int ar_length,int *ptr_array)
{
	
	int *copyA,i;
	copyA = (int*)malloc(ar_length*sizeof(int));
	
	if (NULL == copyA)
	{
		return NULL;
	}
	
	for (i=0;i<ar_length;i++)
	{
		*(copyA+i) = *(ptr_array+i);
		printf("copyA[%d] is %d\n", i,copyA[i]);
	}
	
return copyA;
}

void SwapSizeT(size_t *st1,size_t *st2)
{
	long unsigned int holder = *st1;
	*st1 = *st2;
	*st2 = holder;
  	return;
}







	
