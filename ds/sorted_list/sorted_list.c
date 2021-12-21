#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */
#include <string.h>

#include "sorted_list.h"
#include "dll.h"

/***********************************
 * Sorted Linked List WS		   *
 *           	   *
 * by Tanya					       *
 *   			           *
 *                                 *
 * Reviewer:                 *
 ***********************************/


enum stats
{
    FAIL = -1,
    SUCCESS,
    FOUND
};

struct sort_list
{
    dlist_t *dll;
    cmp_func_t sort_func;
};


int CompareData(const void *left, const void *right)
{

    return (*(size_t *)left - *(size_t *)right);
   
}


sort_list_t *SortListCreate(cmp_func_t sort_func)
{
    sort_list_t *sortl = NULL;

    assert(NULL != sort_func);

    sortl = (sort_list_t *)malloc(sizeof(sort_list_t));
    sortl->dll = DListCreate();

    if(NULL == sortl || NULL == sortl->dll)
    {
        free(sortl->dll);
        free(sortl);
        return NULL;
    }
    sortl->sort_func = sort_func;

    return sortl;
}

void SortListDestroy(sort_list_t *slist)
{
    DListDestroy(slist->dll);
    memset(slist, 0, sizeof(sort_list_t));
    slist->dll = NULL;
   
    free(slist);
    slist = NULL;
}

size_t SortListSize(const sort_list_t *slist)
{
    assert(NULL != slist);
    
    return DListSize(slist->dll);
}


int SortListIsEmpty(const sort_list_t *slist)
{
    assert(NULL != slist);
    
    return DListIsEmpty(slist->dll);
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

sort_list_iter_t SortListInsert(sort_list_t *slist, void *data)
{
   
    sort_list_iter_t datas;

    int comp = 1;

    assert(NULL != slist);
    
    datas.diter = DListBegin(slist->dll);
   
    while(!DListIsEqual(DListEnd(slist->dll), datas.diter) &&  (comp > 0) )
    { 
        comp = CompareData(DListGetData(datas.diter), data);
        datas.diter = DListNext(datas.diter);
        printf("comp is %d\n", comp);
    }

    datas.diter = DListInsert(datas.diter, data);
    return datas;
}


sort_list_iter_t SortListRemove(sort_list_iter_t iter)
{
    iter.diter = DListRemove(iter.diter);
    return iter;
}


sort_list_iter_t SortListBegin(const sort_list_t *slist)
{
    sort_list_iter_t holder;
    assert(NULL != slist);

    holder.diter = DListBegin(slist->dll);
    #ifdef DEBUG
    iter.slist = slist;
    #endif

    return holder;
}

sort_list_iter_t SortListEnd(const sort_list_t *slist)
{
    sort_list_iter_t holder;
    assert(NULL != slist);

    holder.diter = DListEnd(slist->dll);
     #ifdef DEBUG
    iter.slist = slist;
    #endif

    return holder;
}

void *SortListGetData(sort_list_iter_t iter)
{
    return DListGetData(iter.diter);
}

void *SortListPopFront(sort_list_t *slist)
{
    void *data = NULL;
    
    assert(NULL != slist);

    data = DListPopFront(slist->dll);
    return data;
}

void *SortListPopBack(sort_list_t *slist)
{
    void *data = NULL;
    assert(NULL != slist);

    data = DListPopBack(slist->dll);
    return data;
}

int SortListIterIsEqual(sort_list_iter_t iter1, sort_list_iter_t iter2)
{
    return DListIsEqual(iter1.diter, iter2.diter);
}

sort_list_iter_t SortListNext(sort_list_iter_t iter)
{
    iter.diter = DListNext(iter.diter);
    return iter;
}

sort_list_iter_t SortListPrev(sort_list_iter_t iter)
{
    iter.diter = DListPrev(iter.diter);
    return iter;  
}

int SortListForEach(sort_list_iter_t from, sort_list_iter_t to, action_func_t action_func, void *param)
{
    return (DListForEach(from.diter, to.diter, action_func, param));

}

sort_list_iter_t SortListFindIf(sort_list_iter_t from, sort_list_iter_t to, match_func_t match_func, const void *param)
{
    from.diter = DListFind(from.diter, to.diter, match_func, (void *)param);
    return from;
}

void SortListMerge(sort_list_t *dest, sort_list_t *src)
{
    dlist_iter_t runner_where = NULL;
    dlist_iter_t run_to = NULL;

    assert(NULL != dest);
    assert(NULL != src);

    runner_where = DListBegin(dest->dll);
    run_to = DListBegin(src->dll);

    while(!DListIsEqual(runner_where, DListEnd(dest->dll)))
    {
        while (0 > dest->sort_func(runner_where, run_to))
        {
            run_to = DListNext(run_to);
        }
        DListSplice(runner_where, DListBegin(src->dll), run_to);
        runner_where = DListNext(runner_where);
    }

}