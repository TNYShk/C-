/**********************************
 * Heap - Source Code          	  *
 * Developer: Tanya               *
 * Feb 10, 2022                   *
 *                                *
 *      reviewed by               *
***********************************/
#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memmove                      */
#include <assert.h>    /* assert                      */ 


#include "heap.h"


int CompareData(const void *data1, const void *data2);



int main(void)
{
    heap_t *heap = NULL;
    heap = HeapCreate(&CompareData);
    HeapDestroy(heap);
    
    return 0;
}

int CompareData(const void *data1, const void *data2)
{
    return (*(size_t *)&data1 - *(size_t *)&data2);
}