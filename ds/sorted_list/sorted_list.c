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
    cmp_func_t cmp;
};


int CompareData(const void *left, const void *right)
{

    return (*(size_t *)left < *(size_t *)right);
   
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
    sortl->cmp = sort_func;

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
    int comp = 0;

    assert(NULL != slist);
    
    datas = SortListBegin(slist);
    comp = CompareData(SortListGetData(SortListPrev(SortListEnd(slist))),data);

    while (comp)
    {
        comp = CompareData(SortListGetData(SortListNext(datas)),data);
    }
    
    datas.diter = DListInsert(datas.diter,data);
    return datas;
}


sort_list_iter_t SortListRemove(sort_list_iter_t iter);


sort_list_iter_t SortListBegin(const sort_list_t *slist)
{
    sort_list_iter_t holder;
    assert(NULL != slist);

    holder.diter = DListBegin(slist->dll);
    

    return holder;
}

sort_list_iter_t SortListEnd(const sort_list_t *slist)
{
    sort_list_iter_t holder;
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