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
int MatchNums(const void *data, void *param);
void TestOne();
void TestTwo();




static void PrintSListForward(const sort_list_t *slist)
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


int main(void)
{
    TestOne();
   
    return 0;
}

void TestOne()
{
        pq_t *test = NULL;
        size_t one = 1;
        size_t hund = 100;
        int ans = 0;
        test = PQCreate(CompareData);
        (PQIsEmpty(test) == 0) ? printf("not empty\n") : printf("empty\n");
        ans = PQEnqueue(test, &one);
        (PQIsEmpty(test) == 0) ? printf("not empty\n") : printf("empty\n");
        assert(PQSize(test) == 1);
        printf("size is %d\n", ans);
        ans = PQEnqueue(test, &hund);
        assert(PQSize(test) == 2);
        printf("size is %d\n", ans);
        PQDestroy(test);
}




int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}
