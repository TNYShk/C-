#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */



/****************** reviewed by Nurit***********/
/**********i havent tested Find***********/
#include "sll.h"

enum stats
{
	FAIL = -1, 
	NOTK, 
	OK
};

struct slist
{
    slist_iter_t head;
    slist_iter_t tail; 
};

struct slist_node
{
    void *data;
    slist_iter_t next;
};


slist_t *SListCreate(void)
{
	
	slist_t *slist = NULL;
	slist_iter_t dummy = NULL;

	slist = (slist_t *)malloc(sizeof(slist_t));

	if(NULL == slist)
	{
		return NULL;
	}

	dummy = (slist_iter_t)malloc(sizeof(struct slist_node));
	
	if (NULL == dummy)
	{
		free(slist);
		slist = NULL;
		return NULL;
	}
	
	dummy->data = slist;
	dummy->next = NULL;

	slist->head = dummy;
	slist->tail = dummy;
	
	return slist;
}

void SListDestroy(slist_t *slist)
{
	slist_iter_t next = NULL;
	slist_iter_t current =  slist->head;

	assert(NULL != slist);

	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}

	free(slist);
	slist = NULL;
}


slist_iter_t SListInsertBefore(const slist_iter_t where, void *data)
{
	slist_iter_t temp = NULL;
	temp = (slist_iter_t)malloc(sizeof(struct slist_node));

 	assert(NULL != data);
 	assert(NULL != where);

	if (NULL == temp)
	{
		temp = where;
		while (NULL != temp->next)
		{
			temp = temp->next;
		}
		return temp;
	}

	assert (NULL != where);

	if (SListIsEqual(((slist_t *)(where->data))->head, ((slist_t *)(where->data))-> tail))
    {
		temp->next = where;
	    temp->data = data; 
	    ((slist_t *)(where->data))->head = temp;

	    return temp;
    }
	temp->data = where->data;
	temp->next = where->next;
	where->data = data; 
	where->next = temp;

	return where;
}


slist_iter_t SListInsertAfter(slist_iter_t where,  void *data)
{
	slist_iter_t node_after = NULL;
	
	assert(NULL != data);
 	assert(NULL != where);

	node_after = (struct slist_node *)malloc(sizeof(struct slist_node));
	
	if (NULL == node_after)
	{
		node_after = where;
		while (NULL != node_after->next)
		{
			node_after = node_after->next;
		}
		return node_after;
	}

	node_after->data = data; 
	node_after->next = where->next;
	where->next = node_after;
	
	if(NULL == node_after->next) /* if the newly added element is now the last-dummy, need to reassign tail*/
	{
		((slist_t *)(where->data))->tail = node_after;
	}
	return node_after;
}


void *SListGetData( slist_iter_t iterator)
{
	assert (NULL != iterator);

	return iterator->data;
}


void SListSetData(slist_iter_t iterator, void *data)
{
	assert (NULL != iterator);
	assert (NULL != data);

	iterator->data = data; 
}


int SListIsEmpty(const slist_t *slist)
{
	assert (NULL != slist);

	return (slist->head == slist->tail);
}


slist_iter_t SListNext(const slist_iter_t iterator)
{
	if(NULL == iterator->next)
	{
		return iterator;
	}
	return iterator->next;
}


slist_iter_t SListRemove(slist_iter_t iterator)
{
	slist_iter_t replacement = NULL;
	
	if(NULL == iterator->next)
	{
		printf("cant remove dummy!\n");
		return iterator;
	}
	
	replacement = iterator->next;
	iterator->data = replacement->data;
	iterator->next = replacement->next;
	
	if(NULL == iterator->next)
	{
		((slist_t *)(iterator->data))->tail = iterator;
	}

	free(replacement);
	replacement = NULL;

	return iterator;
}


size_t SListCount(const slist_t *slist)
{
	size_t counter = 0;
	slist_iter_t current = slist->head;

	assert(NULL != slist);

	while(current->next != NULL)
	{
		++counter;
		current = current->next;
	}
	return counter;
}


slist_iter_t SListBegin(const slist_t *slist)
{
	assert (NULL != slist);

	return slist->head;
}

slist_iter_t SListEnd(const slist_t *slist)
{
	assert (NULL != slist);

	return slist->tail;
}

int SListIsEqual(const slist_iter_t iterator1, const slist_iter_t iterator2)
{
	return ( iterator1 == iterator2);
}

slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to, match_func_t is_match, void *param)
{
    slist_iter_t temp_result = NULL;
    
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != param);
    
    temp_result = from;
    
    while (!SListIsEqual(to, temp_result))
    {
       if(is_match(temp_result->data, param))
       {
       		return temp_result;
       }
    
    temp_result = SListNext(temp_result);
    }
    
    return NULL;
}


int SListForEach( slist_iter_t from,  slist_iter_t to, action_func_t action_func, void *param)
{
    slist_iter_t current = NULL;
    int ans = FAIL;
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != param);
    
    current = from;
    
    while (current != to)
    {
        
        ans = action_func(current->data, param);
        current = SListNext(current);
    }
    
    return ans;
}


void SlistAppend(slist_t *dest, slist_t *src)
{
	dest->tail->data = SListGetData(SListBegin(src));
	dest->tail->next = src->head->next;
	dest->tail = SListEnd(src);

	src->head->data = src;
	src->head->next = NULL;
	src->tail = SListBegin(src);
	
}
