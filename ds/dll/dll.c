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
   	node =  InitLNode(node, data);

    assert(NULL != where);

	if (NULL == node)
	{
		return where;
	}
    if (NULL == where->prev)
    {
    	((dlist_t *)(where->data))->head->next = node;
    }

    where->prev->next = node;
    node->next = where;
    node->prev = where->prev;

    return node; 
}


dlist_iter_t DListRemove(dlist_iter_t iter)
{
    dlist_iter_t remove = NULL;

    if( (NULL == iter->next ) || (NULL == iter->prev) )
    {
		printf("cant remove dummy!\n");
		return iter;
    }

    remove = iter->next;
    iter->data = remove->data;
    iter->next = remove->next;

    free(remove);
    remove = NULL;

    return iter;

}


dlist_iter_t DListBegin(const dlist_t *dll)
{
     assert(NULL != dll);

     return dll->head->next;
}


dlist_iter_t DListEnd(const dlist_t *dll)
{
     assert(NULL != dll);

     return dll->tail->prev;
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

