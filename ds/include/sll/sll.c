#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "sll.h"

enum 
{
	FAIL = -1, 
	NOTK, 
	OK
};

struct slist
{
    slist_iter_t head;
    slist_iter_t tail; /* tail is the dummy it moves */
};

struct slist_node
{
    void *data;
    slist_iter_t next;
};


slist_t *SListCreate(void)
{
	
	slist_t *sllist = NULL;
	slist_iter_t dummy = NULL;

	sllist = (slist_t *)malloc(sizeof(slist_t));

	if(NULL == sllist)
	{
		return NULL;
	}

	dummy = (slist_iter_t)malloc(sizeof(struct slist_node));
	
	if (NULL == dummy)
	{
		free(sllist);
		sllist = NULL;
		return NULL;
	}
	
	dummy->data = sllist;
	dummy->next = NULL;

	sllist->head = dummy;
	sllist->tail = dummy;
	return sllist;
}

void SListDestroy(slist_t *slist)
{
	slist_iter_t next = NULL;
	slist_iter_t current =  slist->head;

	assert(NULL != slist);

	
	while (current != slist->tail)
	{
		next = current->next;
		free(current);
		current = next;
	}

	free(slist->tail);
	slist->tail = NULL;
	free(slist);
	slist = NULL;
}



slist_iter_t SListInsertBefore(const slist_iter_t where, const void *data)
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
	    temp->data = (void *)data; 
	    ((slist_t *)(where->data))->head = temp;
	    return temp;
    }
	
	temp->data = where->data;
	temp->next = where->next;
	where->data = (void *)data; 
	where->next = temp;

	return where;
}


slist_iter_t SListInsertAfter(slist_iter_t where, const void *data)
{
	slist_iter_t node_after = NULL;
	node_after = (struct slist_node *)malloc(sizeof(struct slist_node));
	
	if (NULL == node_after)
	{
		/* malloc failed */
		return SListNext(where);
	}

	node_after->data = (void *)data; 
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


void SListSetData(slist_iter_t iterator, const void *data)
{
	
	assert (NULL != iterator);
	assert (NULL != data);

	iterator->data = (void *)data; 
	
}


int SListIsEmpty(const slist_t *slist)
{
	assert (NULL != slist);
	return (slist->head == slist->tail);
}


slist_iter_t SListNext(const slist_iter_t iterator)
{
	if(iterator->next == NULL)
	{
		return iterator;
	}
	return iterator->next;
}



/* not*/
void SlistAppend(slist_t *dest, slist_t *src)
{
	
	dest -> tail -> data = src -> head -> data;
	dest -> tail -> next = src -> head -> next;
	
	dest -> tail = src -> tail;
	
	src -> head -> data = src;
	src -> head -> next = NULL;
	
	src -> tail = src -> head;

	/*
	slist_iter_t new_src = SListBegin(src);
	dest -> tail->next  = SListBegin(src);
	dest ->tail->data = SListGetData(SListBegin(src));
	dest->tail = SListEnd(src);
	src->head = new_src;
	src->tail = dest->tail;
	*/
}


slist_iter_t SListRemove(slist_iter_t iterator)
{
	slist_iter_t replacement = NULL;
	
	if(NULL == iterator->next)
	{
		printf("cant remove this node dummy!\n");
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

	while(current != slist->tail)
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
    int match = 0;
    
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != param);
    
    temp_result = from;
    
    while (!SListIsEqual(to, temp_result))
    {
        match = is_match(temp_result->data, param);
        
        if (OK == match)
        {
            return temp_result;
        }
        
        temp_result = SListNext(temp_result);
    }
    
    return NULL;
}


int SListForEach(const slist_iter_t from, const slist_iter_t to, action_func_t action_func, void *param)
{
    slist_iter_t current = NULL;
    
    int result = 0;
    
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != param);
    assert(NULL != action_func);
    
    current = from;
    
    while (!SListIsEqual(to, current))
    {
        result = action_func(current->data, param);
        if (FAIL == result)
        {
            return result;
        }
        current = SListNext(current);
    }
    
    return result;
}

