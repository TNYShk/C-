/***********************************
 * Sorted Linked List WS		   *
 *           	   *
 * by Tanya					       *
 *   			           *
 *                                 *
 * Reviewer:                 *
 ***********************************/

#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include <string.h>
#include "dll.h"
#include "sorted_list.h"



#define PRINT_NODE(node) (printf("node at address %p has int %d, prev is %p, next is %p\n", \
        (void *)node, *(int *)DListGetData(node), (void *)DListPrev(node), (void *)DListNext(node)));


static void PrintDListForward(const dlist_t *dlist)
{
    
    dlist_iter_t runner = NULL;
    
    assert(NULL != dlist);
    
    runner = DListPrev(DListBegin(dlist));
    
    printf("\n-------List is:------\n");
    
    while (runner != NULL)
    {
        PRINT_NODE(runner);
        runner = DListNext(runner);
    }
    printf("Size of list is: %lu. List %s.\n", DListSize(dlist), DListIsEmpty(dlist) ? "is empty" : "is not empty");
}


/*
typedef int (*cmp_func_t)(const void *left, const void *right);

typedef struct sort_list sort_list_t;
typedef struct sort_list_iter sort_list_iter_t;

struct sort_list_iter
{
    dlist_iter_t diter;            
#ifdef DEBUG
    sort_list_t *slist;
#endif
};
*/

int CompareData(const void *left, const void *right);



int main (void)
{
    size_t x = 6;
    size_t y = 7;

    sort_list_t *test = NULL;
    sort_list_iter_t iter1,iter2;
    test = SortListCreate(CompareData);
  
    
    iter1 = SortListInsert(test, &x);
    iter2 = SortListInsert(test, &y);

   (SortListSize(test) > 0)? printf("size is %ld\n",SortListSize(test)) : printf("empty list\n");
    
   (SortListIsEmpty(test) == 1)? printf("IsEmpty -empty list\n") : printf("Not empty list\n");

 

   
 



    SortListDestroy(test);


    return 0;
}

