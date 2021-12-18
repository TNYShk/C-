#include <stdio.h> /* printf, size_t  */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert() */

/****************** reviewed by Nurit **********
 * updated file on 18_12
 * 
 * */



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


static slist_iter_t InitNode(slist_iter_t new_node,void *data)
{
	new_node = (struct slist_node *)malloc(sizeof(struct slist_node));

	if(new_node != NULL)
	{
		new_node->data = data;
		new_node->next = NULL;
		return new_node;
	}
	
	return NULL;
}


slist_t *SListCreate(void)
{
	
	slist_t *slist = NULL;
	slist_iter_t dummy = NULL;

	slist = (slist_t *)malloc(sizeof(slist_t));
	dummy = InitNode(dummy,slist);

	if( (NULL == slist) || (NULL == dummy) )
	{
		free(slist);
		slist = NULL;
		
		return NULL;
	}
	slist->head = dummy;
	slist->tail = dummy;
	
	return slist;
}

void SListDestroy(slist_t *slist)
{
	slist_iter_t next = NULL;
	slist_iter_t current =  SListBegin(slist);

	assert(NULL != slist);

	while (current != NULL)
	{
		next = SListNext(current);
		free(current);
		current = next;
	}

	free(slist);
	slist = NULL;
}


slist_iter_t SListInsertBefore(const slist_iter_t where, void *data)
{
	slist_iter_t temp = NULL;
	temp = InitNode(temp, data);
	
 	assert(NULL != where);

	if (NULL == temp)
	{
		temp = where;
		while (NULL != temp->next)
		{
			temp = SListNext(temp);
		}
		return temp;
	}
	
	if (NULL == where->next)
	{
		((slist_t *)(where->data))->tail = temp;
	}

		temp->data = where->data;
		temp->next = SListNext(where);
		
		where->data = data; 
		where->next = temp;
		
		return where;
}




slist_iter_t SListInsertAfter(slist_iter_t where, void *data)
{
	slist_iter_t node_after = NULL;
	node_after = InitNode(node_after, data);

 	assert(NULL != where);
	
	if (NULL == node_after)
	{
		node_after = where;
		node_after->next = SListNext(where);
		while (NULL != node_after->next)
		{
			node_after = SListNext(node_after);
		}
		return node_after;
	}

	node_after->next = SListNext(where);
	where->next = node_after;
	
	/* if the newly added element is now the last-dummy, need to reassign tail*/
	if(NULL == node_after->next) 
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

	iterator->data = data; 
}


int SListIsEmpty(const slist_t *slist)
{
	assert (NULL != slist);

	return (slist->head == slist->tail);
}


slist_iter_t SListNext(const slist_iter_t iterator)
{
	assert (NULL != iterator);

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
	
	replacement = SListNext(iterator);
	iterator->data = SListGetData(replacement);
	iterator->next = SListNext(replacement);
	
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
	slist_iter_t current = SListBegin(slist);

	assert(NULL != slist);

	while(current->next != NULL)
	{
		++counter;
		current = SListNext(current);
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
	return (iterator1 == iterator2);
}

slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to, match_func_t is_match, void *param)
{
    slist_iter_t temp_result = NULL;
    size_t counter = 0;
    assert(NULL != from);
    assert(NULL != to);
 
    temp_result = from;
    
    while (temp_result!= NULL)
    {
       if(is_match(temp_result->data, param))
       {
       		printf("\nlocated %ld elements from 'from'  ",counter);
       		return temp_result;
       }
    ++counter;
    temp_result = SListNext(temp_result);
    }
    
    return NULL;
}


int SListForEach( slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param)
{
    slist_iter_t current = NULL;
    int ans = FAIL;

    assert(NULL != from);
    assert(NULL != to);
  
    current = from;
    
    while (!SListIsEqual(current, to))
    {
        ans = action_func(current->data, param);
        current = SListNext(current);
    }
    
    return ans;
}


void SlistAppend(slist_t *dest, slist_t *src)
{
	dest->tail->next = src->head->next;
    dest->tail->data = src->head->data;
	
	dest->tail = SListEnd(src);
	dest->tail->data = dest;

	src->head->data = src;
	src->head->next = NULL;
	src->tail = SListBegin(src);
	
}
	
    
    