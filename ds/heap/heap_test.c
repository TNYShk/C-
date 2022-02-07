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
int IsMatch(const void *element, const void *param);

static void CreateDestroy();
static void HeapSiz();
static void HeapTest();
static void RemoveTest();


int main(void)
{
    CreateDestroy();
    HeapSiz();
    RemoveTest();
    HeapTest();
    return 0;
}






static void CreateDestroy()
{
    heap_t *hippie = NULL;

    hippie = HeapCreate(CompareData);
    assert(1 == HeapIsEmpty(hippie));
    assert(0 == HeapSize(hippie));
    HeapDestroy(hippie);
    printf("\nCreate Destroy PASSED\n");
}

static void HeapSiz()
{
    heap_t *hippie = NULL;
    int a =  5;
    int b = 6;
    int c = 2;
    int d = 4;
    int e = 16;

    hippie = HeapCreate(CompareData);
    assert(1 == HeapIsEmpty(hippie));
    assert(0 == HeapSize(hippie));
    assert(0 == HeapPush(hippie, &a));
    assert(0 == HeapPush(hippie, &b));
    assert(0 == HeapPush(hippie, &c));
    assert(0 == HeapPush(hippie, &d));
    assert(0 == HeapPush(hippie, &e));
    assert(5 == HeapSize(hippie));
     printf("\nHeap Push PASSED\n");
    printf("\nHeap Size PASSED\n");
     HeapPop(hippie);
      HeapPop(hippie);
       HeapPop(hippie);
        HeapPop(hippie);
         HeapPop(hippie);
    assert(0 == HeapSize(hippie));
    printf("\nHeap Pop PASSED\n");
    HeapDestroy(hippie);

    
}

static void RemoveTest()
{
    heap_t *hippie = NULL;
    void *rem = NULL;
    void *rr = NULL;
    int a =  5;
    int b = 6;
    int c = 2;
    int d = 4;
    int e = 16;

    hippie = HeapCreate(CompareData);
    assert(1 == HeapIsEmpty(hippie));
    assert(0 == HeapSize(hippie));
    assert(0 == HeapPush(hippie, &a));
    assert(0 == HeapPush(hippie, &b));
    assert(0 == HeapPush(hippie, &c));
    assert(0 == HeapPush(hippie, &d));
    
    assert(4 == HeapSize(hippie));
    printf("\nRemoving\n");

    rem = HeapRemove(hippie, &IsMatch, &b);
    assert(*(int*)rem == b);
    rem = HeapRemove(hippie, &IsMatch, &a);
    assert(*(int*)rem == a);
    HeapRemove(hippie, &IsMatch, &c);
    rr = HeapRemove(hippie, &IsMatch, &e);
    assert(*(int*)rr == e);


    assert(1 == HeapSize(hippie));
    printf("\nHeap Remove PASSED?\n");
    HeapDestroy(hippie);
}

void HeapTest()
{
    heap_t *hippie = NULL;
    int a =  5;
    int b = 6;
    int c = 2;
    int d = 4;
    int e = 16;
    void *ptr = NULL;
    void *p2 = NULL;
    hippie = HeapCreate(CompareData);
   
    assert(1 == HeapIsEmpty(hippie));

    (1 == HeapIsEmpty(hippie))? printf("Empty Heap\n") : printf("NOT empty Heap\n");
    printf("size? %ld\n", HeapSize(hippie));
    
    printf("\nPushing Elements\n");
    HeapPush(hippie, &a);
   
    printf("\n\tpeeking: %d\n", *(int*)HeapPeek(hippie));
    
    assert(0 == HeapPush(hippie, &b));
    printf("\n\tpeeking: %d\n", *(int*)HeapPeek(hippie));
    printf("pushed, size? %ld\n", HeapSize(hippie) );
    
    HeapPush(hippie, &c);
    ptr = HeapPeek(hippie);
    printf("\n\tstill peeking: %d\n", *(int*)ptr);
    printf("pushed, size %ld\n", HeapSize(hippie) );
    
    HeapPop(hippie);
    printf("pop, size? %ld\n", HeapSize(hippie) );
   
    ptr = HeapRemove(hippie, &IsMatch, &b);
    printf("\n\tremoved %d\n", *(int*)ptr);
    printf("size? %ld\n", HeapSize(hippie) );
    
    HeapPush(hippie, &d);
    printf("pushed, size is %ld\n", HeapSize(hippie) );
    ptr = HeapPeek(hippie);
    printf("\n\tpeeking into root: %d\n", *(int*)ptr);


    p2 = HeapRemove(hippie, &IsMatch, &e);
    printf("\n\tremoved? %d\n", *(int*)p2);
     printf("size? %ld\n", HeapSize(hippie) );
   /*
    printf("\nPoping root\n");
    HeapPop(hippie);
    ptr = HeapPeek(hippie);
    printf("\n\tstill peeking: %d\n", *(int*)ptr);
    printf("size? %ld\n", HeapSize(hippie) );
    */
   
    HeapDestroy(hippie);
}




int CompareData(const void *data1, const void *data2)
{
    return *(int *)data1 - *(int *)data2;
}

int IsMatch(const void *element, const void *param)
{
    return (CompareData(element,param) == 0);
}


