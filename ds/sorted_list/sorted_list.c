/***********************************
 * Sorted Linked List WS           *
 *                                 *
 * by Tanya    Dec 22 2021         *
 *                                 *
 *                                 *
 * Reviewer:  Amit                 *
 ***********************************/

#include <stdio.h>  /* printf, size_t      */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert()          */
#include <string.h> /*memset            */

#include "dll.h" /*  double linked list funcs */
#include "sorted_list.h"



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


sort_list_t *SortListCreate(cmp_func_t sort_func)
{
    sort_list_t *sortl = NULL;

    assert(NULL != sort_func);

    sortl = (sort_list_t *)malloc(sizeof(sort_list_t));
    if(NULL == sortl)
    {
        return NULL;
    }

    sortl->dll = DListCreate();
    if(NULL == sortl->dll)
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

sort_list_iter_t SortListInsert(sort_list_t *slist, void *data)
{
    
    sort_list_iter_t runner = {0};

    assert(NULL != slist);
    
    runner.diter = DListBegin(slist->dll);

    while(!DListIsEqual(runner.diter, DListEnd(slist->dll)) && 
         (0 < slist->sort_func(data, DListGetData(runner.diter))) )
    { 
        runner.diter = DListNext(runner.diter);
    }
    runner.diter = DListInsert(runner.diter, data);
    return runner;
}

sort_list_iter_t SortListRemove(sort_list_iter_t iter)
{
    iter.diter = DListRemove(iter.diter);
    return iter;
}

sort_list_iter_t SortListBegin(const sort_list_t *slist)
{
    sort_list_iter_t holder = {0};
    
    assert(NULL != slist);

    holder.diter = DListBegin(slist->dll);
    return holder;
}

sort_list_iter_t SortListEnd(const sort_list_t *slist)
{
    sort_list_iter_t holder = {0};
    
    assert(NULL != slist);

    holder.diter = DListEnd(slist->dll);
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
    int ans = DListForEach(from.diter, to.diter, action_func, param);
    #ifdef DEBUG
        assert(from.slist == to.slist);
    #endif

    return ans;
}

sort_list_iter_t SortListFindIf(sort_list_iter_t from, sort_list_iter_t to, match_func_t match_func, const void *param)
{
    sort_list_iter_t iter = {0};
    assert(NULL != match_func);

    iter.diter = DListFind(from.diter, to.diter, match_func, (void *)param);
    return iter;
}
/* will sit on this on the weekend, write new pseudo */
void SortListMerge(sort_list_t *dest, sort_list_t *src)
{
    sort_list_iter_t where_dest = {0};
    sort_list_iter_t from_src = {0};
    sort_list_iter_t src_end = {0};
  
    assert(NULL != dest);
    assert(NULL != src);
       
    where_dest = SortListBegin(dest);
    from_src =  SortListBegin(src);
    src_end = SortListEnd(src);
   
    while(where_dest.diter !=  SortListEnd(dest).diter)
    {
        while ( (from_src.diter != src_end.diter ) &&
           ( 0 < dest->sort_func(SortListGetData(where_dest), SortListGetData(from_src))) )
        {
            from_src = SortListNext(from_src);
        }
        if(from_src.diter != SortListBegin(src).diter)
        {
            DListSplice(where_dest.diter, SortListBegin(src).diter, from_src.diter);
        }
        where_dest = SortListNext(where_dest);
    } 
    /* if something overlooked, pop one by one */
      if(!SortListIsEmpty(src))
    {
        SortListInsert(dest, SortListPopBack(src));
    }
   /** O(n*m) ****
    while(!SortListIsEmpty(src))
    {
        SortListInsert(dest, SortListPopBack(src));
        SortListInsert(dest, SortListPopFront(src));
   */
}



sort_list_iter_t SortListFind(sort_list_t *slist, sort_list_iter_t from, sort_list_iter_t to, const void *data)
{
    
    assert(NULL != slist);

    while(!SortListIterIsEqual(from, to))
    {
        if (0 == slist->sort_func(SortListGetData(from), data))
        {
            return from;
        }
        from = SortListNext(from);
    }

    return to;
}





 