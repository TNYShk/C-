/**********************************************
 * Priority Q test file- WS                   *
 * Developer: Tanya                           *
 * Written: 2021-12-23                        *
 *                                            *
 * Reviewer:  Ori Marom                       *
 **********************************************/

#include <stdio.h>  /* printf, size_t      */
#include <assert.h> /* assert()          */


#include "pq.h"
#include "sorted_list.h"


int CompareData(const void *left, const void *right);
int MatchData(const void *data, const void *param);
void TestOne();
void TestTwo();
void TestPeekAndDequeueTest(pq_t *pq);




int main(void)
{
    TestOne(); 
    TestTwo();

    return 0;
}

void TestOne()
{
    pq_t *test = NULL;
    size_t one = 1;
    size_t hund = 100;
    size_t huns = 101;
    int ans = 0;
    test = PQCreate(CompareData);
    printf("\n\n\t-----------------------------Test 1-------------------------------\n");
    (PQIsEmpty(test) == 0) ? printf("PQ Not empty\n") : printf("Empty PQ\n");
    ans = PQEnqueue(test, &one);
    (PQIsEmpty(test) == 0) ? printf("PQ Not empty\n") : printf("Empty PQ\n");
    assert(PQSize(test) == 1);
    printf("PQ ENQ ans  is %d\n", ans);
    ans = PQEnqueue(test, &hund);
    printf("PQ ENQ ans  is %d\n", ans);
    assert(PQSize(test) == 2);
    printf("size is %ld\n", PQSize(test));

    printf("\t--------------inserting 2 more--------------------\n");
    PQEnqueue(test, &hund);
    PQEnqueue(test, &huns);
    printf("size is %ld\n", PQSize(test));
    
    printf("\t--------------Dequeue ALL --------------------\n");
    TestPeekAndDequeueTest(test);
    
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
    pq_match_func_t foo = &MatchData;

    test = PQCreate(CompareData);
    printf("\n\n\t-----------------------------Test 2-------------------------------\n");
    (PQIsEmpty(test) == 0) ? printf("PQ Not empty\n\n") : printf("Empty PQ\n\n");
    printf("\t--------------PQ EnQ 1--------------------\n");
    ans = PQEnqueue(test, &one);
    (PQIsEmpty(test) == 0) ? printf("PQ Not empty\n\n") : printf("Empty PQ\n\n");
    assert(PQSize(test) == 1);
    printf("size is %d\n", ans);
    ans = PQEnqueue(test, &hund);
    assert(PQSize(test) == 2);
    printf("size is %ld\n", PQSize(test));
    printf("\t--------------inserting 3 more--------------------\n");
    PQEnqueue(test, &hund);
    PQEnqueue(test, &huns);
    PQEnqueue(test, &hund);
    printf("size is %ld\n", PQSize(test));
    printf("\t--------------Peek in PQ--------------------\n");
        
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
    
    printf("\t--------------PQErase test remove 101--------------------\n");
    ptr = PQErase(test,foo, &huns);
    printf("Removed data is: %ld\n", *(size_t*)ptr);
    printf("post PQErase: size is %ld\n", PQSize(test));
    printf("\t--------------Peek in PQ--------------------\n");
    ptr = PQPeek(test);
    printf("Peek into PQ: %ld\n", *(size_t*)ptr);
    printf("\t--------------PQErase test remove 101 not there--------------------\n");

    ptr = PQErase(test,foo, &huns);
    printf("post PQErase: size is %ld\n", PQSize(test));
    printf("\t--------------EnQ PQ 1 ------------------------------------\n");
    PQEnqueue(test, &one);
    printf("post ENQ, size is: %ld\n", PQSize(test));
    ptr = PQPeek(test);
    printf("Peek into PQ, value is: %ld\n", *(size_t*)ptr);
    printf("\t--------------PQErase test remove 100 --------------------\n");
    ptr = PQErase(test,foo, &hund);
    printf("Removed data is: %ld\n", *(size_t*)ptr);
    printf("post PQErase: size is %ld\n", PQSize(test));

    PQDestroy(test);
}  




int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}

int MatchData(const void *data, const void *param)
{   
    return (*(size_t *)data == *(size_t *)param);
}

/* Erez printing func */
void TestPeekAndDequeueTest(pq_t *pq)
{
    void *data = NULL;

    while (!PQIsEmpty(pq))
    {
        data = PQPeek(pq); 
        PQDequeue(pq);
        printf("Peek queue. Element is: %ld. After dequeue. size is: %lu\n", *(size_t *)data, PQSize(pq));
    }
} 
