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

	
dlist_t *DListCreate(void)
{
    dlist_t *dll = (dlist_t *)malloc(sizeof(dlist_t));
   
    dlist_node_t *dummy_head = NULL;
    dlist_node_t *dummy_tail = NULL;

    if (NULL == dll)
    {
    	return NULL;
    }
    dll->head = InitLNode(dummy_head, dll);
    dll->tail = InitLNode(dummy_tail, dll);

    
    
	 dll->head->next = dll->tail;
	 dll->tail->prev = dll->head;
    
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

/*
size_t DListSize(const dlist_t *dll)
{
    
}


dlist_iter_t DListInsert(dlist_iter_t iter, void *data)
{
    
}


dlist_iter_t DListRemove(dlist_iter_t iter)
{
    
}


dlist_iter_t DListPushFront(dlist_t *dll, void *data)
{
    
}


dlist_iter_t DListPushBack(dlist_t *dll, void *data)
{
    
}


void *DListPopFront(dlist_t *dll)
{
    
}


void *DListPopBack(dlist_t *dll)
{
    
}


void DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
    
}


dlist_iter_t DListBegin(const dlist_t *dll)
{
    
}


dlist_iter_t DListEnd(const dlist_t *dll)
{
    
}


dlist_iter_t DListNext(dlist_iter_t iter)
{
    
}


dlist_iter_t DListPrev(dlist_iter_t iter)
{
    
}


void *DListGetData(dlist_iter_t iter)
{
    
}


int DListIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
    
}


dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param)
{
    
}

*Return TRUE 1 FALSE 0 and inserts all found into result list *
int DListMultiFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param, dlist_t *result_list)
{
    
}


int DListForEach(dlist_iter_t from, dlist_iter_t to,
	action_func_t action_func, void *param)
{
    
}
*/