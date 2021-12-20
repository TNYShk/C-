#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */

/***********************************
 * Doubly Linked List WS		   *
 * by Tanya					       *
 *             					   *
 *                                 *
 * Reviewer:                       *
 ***********************************/



#include "dll.h"





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
   dlist_node_t *next = NULL;
	dlist_node_t *current =  dll->head;

	assert(NULL != dll);

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

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
     dlist_iter_t counter = dll->head;
     
     assert(NULL != dll);
    
     while (counter->next != dll->tail)
     {
     	++count;
     	counter = counter->next;
     }
     return count;
}


dlist_iter_t DListInsert(dlist_iter_t where, void *data)
{
    dlist_iter_t node = NULL;
   	node =  (dlist_node_t *)malloc(sizeof(dlist_node_t));

    assert(NULL != where);
	
	if (NULL == node)
	{
		return RetrieveTail(where);
	}
	

    node->data = data;
	node->prev = where->prev;
	node->next = where;
	
	where->prev->next = node;
	where->prev = node;

    
    return node; 
}


dlist_iter_t DListRemove(dlist_iter_t iter)
{
    dlist_iter_t remove = NULL;

    assert(NULL != iter);

    if(NULL == iter->next || NULL == iter->prev)
    {
		printf("cant remove dummy!\n");
		return iter;
    }

    remove = iter->next;
    iter->data = DListGetData(remove);
    iter->next = DListNext(remove);

    free(remove);
    remove = NULL;

    return iter;
}


dlist_iter_t DListPushFront(dlist_t *dll, void *data)
{
	dlist_iter_t node = NULL;
   	
	assert(NULL != dll);
	node = DListInsert(DListBegin(dll),data);
	
	if(NULL == node)
	{
		printf("wasnt done, heres the head\n");
		return (DListBegin(dll));
	}
	return node;
}

dlist_iter_t DListPushBack(dlist_t *dll, void *data)
{
	
	assert(NULL != dll);
	
	return DListInsert(DListEnd(dll), data);

}

void *DListPopFront(dlist_t *dll)
{
	void *data = DListGetData(DListBegin(dll));
	DListRemove(DListBegin(dll));
	
	return data;
}

void *DListPopBack(dlist_t *dll)
{
	void *data = DListGetData(DListEnd(dll)->prev);
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

    while ((from != to) && !is_match(from->data, param))
	{
		from = DListNext(from);
	}

	return from;
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, void *param)
{

    int status = -1;

    assert(NULL != from);
    assert(NULL != to);
  
    
    while (!DListIsEqual(from, to))
    {
        status = action_func(from->data, param);
        from = DListNext(from);
    }
    
    return status;
}

int DListMultiFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *param, dlist_t *result_list)
{
	
	while(from != to)
	{
		if(is_match(from->data, param))
		{
			if(DListEnd(result_list) == DListPushBack(result_list, from))
			{
				return 1;
			}
		}

		from = DListNext(from);
	}
	return 0;

}

void DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	dlist_iter_t splice_node = NULL;
    
    assert(NULL != where);
    assert(NULL != from);
    assert(NULL != to);
    
    splice_node = to->prev;
    
    from->prev->next = to;
    to->prev = from->prev;
    
    where->prev->next = from;
    from->prev = where->prev;
    
    splice_node->next = where;
    where->prev = splice_node;
}

