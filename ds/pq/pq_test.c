#include <stdio.h>  /* printf, size_t      */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert()          */
#include <string.h> /* printf           */

#include "dll.h"
#include "sorted_list.h"
#include "priority_queue.h"

#define PRINT_NODE(node) (printf("node at address %p has int %d, prev is %p, next is %p\n", \
        (void *)node, *(int *)DListGetData(node), (void *)DListPrev(node), (void *)DListNext(node)));

int CompareData(const void *left, const void *right);
int MatchData(const void *data, void *param);
void TestOne();
void TestTwo();



/*
static void PrintSListForward(const pq_t *slist)
{
    sort_list_iter_t runner;
    
    assert(NULL != slist);
    
    runner = SortListBegin(slist);
    
    printf("\n-------List is:------\n");
    
    while (!SortListIterIsEqual(runner, SortListEnd(slist)))
    {
        printf("%d ", *(int *)SortListGetData(runner));
        runner = SortListNext(runner);
    }
    printf("\n\nSize of list is: %lu. List %s.\n", SortListSize(slist), SortListIsEmpty(slist) ? "is empty" : "is not empty");
    printf("-------list ends------\n");
}
*/

int main(void)
{
    /*TestOne(); */
    TestTwo();

    return 0;
}

void TestOne()
{
        pq_t *test = NULL;
        size_t one = 1;
        size_t hund = 100;
        size_t huns = 101;
        void *ptr = NULL;
        int ans = 0;
        test = PQCreate(CompareData);
        (PQIsEmpty(test) == 0) ? printf("PQ Not empty\n") : printf("Empty PQ\n");
        ans = PQEnqueue(test, &one);
        (PQIsEmpty(test) == 0) ? printf("PQ Not empty\n") : printf("Empty PQ\n");
        assert(PQSize(test) == 1);
        printf("size is %d\n", ans);
        ans = PQEnqueue(test, &hund);
        assert(PQSize(test) == 2);
        printf("size is %ld\n", PQSize(test));
        printf("\t--------------inserting 2 more--------------------\n");
        PQEnqueue(test, &hund);
        PQEnqueue(test, &huns);
        printf("size is %ld\n", PQSize(test));
        printf("\t--------------Dequeue --------------------\n");
        ptr = PQDequeue(test);
        printf("data in dq is %ld\n", *(size_t*)ptr);
        ptr = PQDequeue(test);
        printf("data in dq is %ld\n", *(size_t*)ptr);
        ptr = PQDequeue(test);
        printf("data in dq is %ld\n", *(size_t*)ptr);
        ptr = PQDequeue(test);
        printf("data in dq is %ld\n", *(size_t*)ptr);
        printf("size is %ld\n", PQSize(test));
        printf("\t--------------inserting 2 more--------------------\n");
        PQEnqueue(test, &hund);
        PQEnqueue(test, &hund);
        printf("size is %ld\n", PQSize(test));

        PQDestroy(test);
}

void TestTwo()
{
        pq_t *test = NULL;
        size_t one = 1;
        size_t hund = 100;
        size_t huns = 101;
        void *ptr = NULL;
        int ans = 0;
        test = PQCreate(CompareData);
        (PQIsEmpty(test) == 0) ? printf("PQ Not empty\n") : printf("Empty PQ\n");
        printf("\t--------------PQ EnQ 1--------------------\n");
        ans = PQEnqueue(test, &one);
        (PQIsEmpty(test) == 0) ? printf("PQ Not empty\n") : printf("Empty PQ\n");
        assert(PQSize(test) == 1);
        printf("size is %d\n", ans);
        ans = PQEnqueue(test, &hund);
        assert(PQSize(test) == 2);
        printf("size is %ld\n", PQSize(test));
        printf("\t--------------inserting 3 more--------------------\n");
        PQEnqueue(test, &hund);
        PQEnqueue(test, &huns);
        PQEnqueue(test, &hund);
        printf("\t--------------Peek in PQ--------------------\n");
        printf("size is %ld\n", PQSize(test));
        ptr = PQPeek(test);
        printf("Peek into PQ: %ld\n", *(size_t*)ptr);
        printf("post peek size unchanged? %ld\n", PQSize(test));
        printf("\t--------------Clear PQ test--------------------\n");
        PQClear(test);
        printf("post clear: size is %ld\n", PQSize(test));
        printf("\t--------------inserting 3 100 and 1 101--------------------\n");
        PQEnqueue(test, &hund);
        PQEnqueue(test, &hund);
        PQEnqueue(test, &hund);
        PQEnqueue(test, &huns);
        printf("post ENQ: size is %ld\n", PQSize(test));
        
        printf("\t--------------PQErase test--------------------\n");
        ans = PQErase(test,&MatchData, &hund);
        printf("post PQErase: size is %ld\n", PQSize(test));

        PQDestroy(test);
}  




int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}

int MatchData(const void *data, void *param)
{   
    return (*(size_t *)data == *(size_t *)param);
}