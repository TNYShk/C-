/**********************************
 * Heap - Source Code          	  *
 * Developer: Tanya               *
 * Feb 10, 2022                   *
 *                                *
 *      reviewed by               *
***********************************/
#include <stdlib.h> /*  size_t dynamic memory allocation */
#include <stdio.h>   /*  standard library               */
#include <string.h>   /*  memset                      */
#include <assert.h>    /* assert                      */ 


#include "heap.h"


int CompareData(const void *data1, const void *data2);



int main(void)
{
    heap_t *hippie = NULL;
    int a =  5;
    int b = 6;
    hippie = HeapCreate(&CompareData);
   
    assert(1 == HeapIsEmpty(hippie));

    (1 == HeapIsEmpty(hippie))? printf("Empty Heap\n") : printf("NOT empty Heap\n");
    printf("size? %ld\n", HeapSize(hippie));
    HeapPush(hippie, &a);
    HeapPush(hippie, &b);
    printf("size? %ld\n", HeapSize(hippie) );

    HeapDestroy(hippie);
    
    return 0;
}

int CompareData(const void *data1, const void *data2)
{
    return *((size_t *)&data1) - *((size_t *)&data2);
}

