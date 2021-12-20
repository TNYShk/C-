#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */

/***********************************
 * Doubly Linked List WS		   *
 *  Proud Surviver           	   *
 * by Tanya					       *
 *   Dec 20				           *
 *                                 *
 * Reviewer: Erez                  *
 ***********************************/

#include "dll.h"

#define SUCCESS (0)
#define FAIL (-1)
#define FOUND (1)


struct dlist
{
	struct dlist_node *head;
	struct dlist_node *tail;
};

typedef struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
} dlist_node_t;


/*****************Service Funcs ******************************/

static dlist_iter_t InitLNode(dlist_iter_t new_e, void *data)
{

	new_e = (dlist_node_t *)malloc(sizeof(dlist_node_t));

	if(NULL != new_e)
	{
		new_e->data = data;
		new_e->prev = NULL;
		new_e->next = NULL;
	}
	return new_e;
}

static dlist_iter_t RetrieveTail(dlist_iter_t iter)
{

	while(NULL != iter->next)
	{
		iter = DListNext(iter);
	}
	return iter;
}
/***************End Service Funcs ******************************/

	
dlist_t *DListCreate(void)
{
    dlist_t *dll = NULL;
   	dlist_node_t *dummy_head = NULL;
    dlist_node_t *dummy_tail = NULL;
	
	dll =  (dlist_t *)malloc(sizeof(dlist_t));
   	
    dummy_head = (dlist_node_t *)malloc(sizeof(dlist_node_t));
    dummy_tail = (dlist_node_t *)malloc(sizeof(dlist_node_t));
    
    if (NULL == dll || NULL == dummy_head || NULL == dummy_tail)
     {
     	free(dll);
     	dll = NULL;
     	free(dummy_head);
     	dummy_head = NULL;
     	free(dummy_tail);
     	dummy_tail = NULL;
     	
     	return NULL;
 	
     }
   	dll->head = dummy_head;
	dll->tail = dummy_tail;
	
	dummy_head->data = dll;
	dummy_head->next = dummy_tail;
	dummy_head->prev = NULL;
	
	dummy_tail->data = dll;
	dummy_tail->next = NULL;
	dummy_tail->prev = dummy_head;

    return dll;
}


void DListDestroy(dlist_t *dll)
{
   	dlist_node_t *current_node = dll->head;
	dlist_node_t *next_node = DListNext(current_node);
	
	while (NULL != next_node)
	{ 
		free(current_node);
		current_node = next_node;
		next_node = DListNext(current_node);
	}
	
	free(current_node);
	current_node = NULL;
	
	free(dll);
	dll = NULL;
}


int DListIsEmpty(const dlist_t *dll)
{
    assert(NULL != dll);

    return (dll->head->next == dll->tail);
}


size_t DListSize(const dlist_t *dll)
{
    size_t count = 0;
    dlist_iter_t runner = dll->head;
     
    assert(NULL != dll);
    
    while (runner->next != dll->tail)
    {
     	++count;
     	runner = DListNext(runner);
    }
    return count;
}


dlist_iter_t DListInsert(dlist_iter_t where, void *data)
{
    dlist_iter_t node = NULL;
   	node = InitLNode(node, data);

    assert(NULL != where);
	
	if (NULL == node)
	{
		return RetrieveTail(where);
	}
	
    node->data = data;
	node->prev = DListPrev(where);
	node->next = where;
	
	where->prev->next = node;
	where->prev = node;

    return node; 
}


dlist_iter_t DListRemove(dlist_iter_t iter)
{

	dlist_iter_t next_node = NULL;

    assert(NULL != iter);

    if(NULL == iter->next || NULL == iter->prev)
    {
		/*printf("cant remove dummy!\n");*/
		return iter;
    }

    next_node = DListNext(iter);
    iter->prev->next = DListNext(iter);
    iter->next->prev = DListPrev(iter);

    free(iter);
    iter = NULL;

    return next_node;
}


dlist_iter_t DListPushFront(dlist_t *dll, void *data)
{
	assert(NULL != dll);
	
	return DListInsert(DListBegin(dll), data);
}


dlist_iter_t DListPushBack(dlist_t *dll, void *data)
{
	assert(NULL != dll);
	
	return DListInsert(DListEnd(dll), data);
}


void *DListPopFront(dlist_t *dll)
{
	void *data = DListGetData(DListBegin(dll));
	
	assert(NULL != dll);

	DListRemove(DListBegin(dll));
	
	return data;
}


void *DListPopBack(dlist_t *dll)
{
	void *data = DListGetData(DListEnd(dll)->prev);
	
	assert(NULL != dll);

	DListRemove(DListEnd(dll)->prev);
	
	return data;
}


dlist_iter_t DListBegin(const dlist_t *dll)
{
    assert(NULL != dll);

    return dll->head->next;
}


dlist_iter_t DListEnd(const dlist_t *dll)
{
    assert(NULL != dll);

    return dll->tail;
}


dlist_iter_t DListNext(dlist_iter_t iter)
{
    assert( NULL != iter);

    return iter->next;
}


dlist_iter_t DListPrev(dlist_iter_t iter)
{
    assert( NULL != iter);

    return iter->prev;
}


void *DListGetData(dlist_iter_t iter)
{
    assert( NULL != iter);

    return iter->data;
}


int DListIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
    
    assert( NULL != iter1);
    assert( NULL != iter2);

    return (iter1 == iter2);
}


dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *param)
{
	
	assert( NULL != from);
	assert( NULL != to);
	
	while (from != to)
	{
		if (is_match(from->data, param))
		{
			return from;
		}
		
		from = DListNext(from);
	}
	
	return NULL;
}


int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, void *param)
{

    int status = FAIL;
    dlist_iter_t current = NULL;

    assert( NULL != from);
    assert( NULL != to);
  
    current = from;
    while (!DListIsEqual(current, to))
    {
        status = action_func(current->data, param);
        current = DListNext(current);
    }
    
    return status;
}


int DListMultiFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *param, dlist_t *result_list)
{
	assert( NULL != from);
    assert( NULL != to);

	while(from != to)
	{
		if(is_match(from->data, param))
		{
			if(DListEnd(result_list) == DListPushBack(result_list, from))
			{
				return FOUND;
			}
		}

		from = DListNext(from);
	}
	
	return SUCCESS;
}


void DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	dlist_iter_t splice_node = NULL;
    
    assert(NULL != where);
    assert(NULL != from);
    assert(NULL != to);
 
    splice_node = DListPrev(to);
    
    from->prev->next = to;
    to->prev = DListPrev(from);
    
    where->prev->next = from;
    from->prev = DListPrev(where);
    
    splice_node->next = where;
    where->prev = splice_node;
}



/*test fir each and find funcs */
int MatchNum(const void *data, void *param)
{	
	assert(NULL != param);

	return (*(size_t *)data == *(size_t *)param);
}

int AddInt(void *data, void *param)
{
	assert( NULL != param);
	
	*(size_t *)data += *(size_t *)param;
	
	return SUCCESS;
}