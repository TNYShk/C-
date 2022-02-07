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
static void HeapPeekTest();
static void RemoveTest();


int main(void)
{
    CreateDestroy();
    HeapSiz();
    RemoveTest();
    HeapPeekTest();
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
    assert(rr == NULL);


    assert(1 == HeapSize(hippie));
    printf("\nHeap Remove PASSED?\n");
    HeapDestroy(hippie);
}

void HeapPeekTest()
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
    assert(0 == HeapPush(hippie, &a));
    printf("\npeeking: %d\n", *(int *)HeapPeek(hippie));
    assert(0 == HeapPush(hippie, &b));
    
    printf("\npeeking: %d\n", *(int*)HeapPeek(hippie));
    printf("pushed, size? %ld\n", HeapSize(hippie) );
    assert(2 == HeapSize(hippie));

    assert(0 == HeapPush(hippie, &c));
 
    printf("\nstill peeking: %d\n", *(int *)HeapPeek(hippie));
    printf("\npushed, size %ld\n", HeapSize(hippie) );
    assert(3 == HeapSize(hippie));
    HeapPop(hippie);

    printf("\npop, size? %ld\n", HeapSize(hippie) );
    assert(2 == HeapSize(hippie));
    ptr = HeapRemove(hippie, &IsMatch, &b);
    printf("\nremoved %d\n", *(int*)ptr);
    printf("\nsize? %ld\n", HeapSize(hippie) );
    
    assert(0 == HeapPush(hippie, &d));

    printf("\npushed, size is %ld\n", HeapSize(hippie) );
    printf("\npeeking into root: %d\n", *(int *)HeapPeek(hippie));

    p2 = HeapRemove(hippie, &IsMatch, &e);
    assert(p2 == NULL);
    printf("\nsize? %ld\n", HeapSize(hippie) );
   
    printf("\nPoping root\n");
    HeapPop(hippie);
    
    printf("\nstill peeking: %d\n", *(int *)HeapPeek(hippie));
    printf("size? %ld\n", HeapSize(hippie) );
    HeapPop(hippie);
    printf("last pop,\nsize %ld\n", HeapSize(hippie) );
    assert(1 == HeapIsEmpty(hippie));
    assert(0 == HeapSize(hippie));
    printf("\nHeap Peek Test SUCCESS\n\n\t GOODBYE\n");

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


