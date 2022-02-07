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
    int c = 2;
    void *ptr = NULL;
    hippie = HeapCreate(&CompareData);
   
    assert(1 == HeapIsEmpty(hippie));

    (1 == HeapIsEmpty(hippie))? printf("Empty Heap\n") : printf("NOT empty Heap\n");
    printf("size? %ld\n", HeapSize(hippie));
    
    printf("\nPushing Elements\n");
    HeapPush(hippie, &a);
    ptr = HeapPeek(hippie);
    printf("\n\tpeeking: %d\n", *(int*)ptr);
    assert(0 == HeapPush(hippie, &b));
  
    ptr = HeapPeek(hippie);
    printf("\n\tpeeking into root: %d\n", *(int*)ptr);
    printf("size? %ld\n", HeapSize(hippie) );
    
    HeapPush(hippie, &c);
    ptr = HeapPeek(hippie);
    printf("\n\tstill peeking: %d\n", *(int*)ptr);
    printf("size? %ld\n", HeapSize(hippie) );
   

    printf("\nPoping root\n");
    HeapPop(hippie);
    ptr = HeapPeek(hippie);
    printf("\n\tstill peeking: %d\n", *(int*)ptr);
    printf("size? %ld\n", HeapSize(hippie) );
   
    HeapDestroy(hippie);
    
    return 0;
}

int CompareData(const void *data1, const void *data2)
{
    return *((int *)data1) - *((int *)data2);
}


