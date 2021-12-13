#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
/*
typedef struct slist slist_t;
typedef struct slist_node* slist_iter_t; 

the itterator uses slist_t and the node uses slist_iter_t ?
*/
#include "sll.h"


struct slist
{
    slist_iter_t head;
    slist_iter_t tail; /* tail is the dummy its moves */
    
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
	
	slist_iter_t current =  slist->head;

	assert(NULL != slist);

	
	while (current != slist->tail)
	{
		current = SListRemove(current);
		
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

	assert (NULL != temp);

	temp->data = where->data;
	temp->next = where->next;

	where->data = memcpy(where->data, data, sizeof(temp));
	where->next = temp;

	return where;


}



slist_iter_t SListInsertAfter(slist_iter_t where, const void *data)
{
	slist_iter_t node_after = NULL;
	node_after = (slist_iter_t)malloc(sizeof(struct slist_node));
	
	assert (NULL != node_after);

	node_after->data = memcpy(where->data,data,sizeof(node_after));
	node_after->next = where->next;
	
	where->next = node_after;

	return where;
}

void *SListGetData( slist_iter_t iterator)
{
	assert (NULL != iterator);

	return (void*)iterator->data;
}

void SListSetData(slist_iter_t iterator, const void *data)
{
	slist_iter_t temp = NULL;
	assert (NULL != iterator);

	temp->data = memcpy(temp->data,data,sizeof(struct slist_node));
	assert (NULL != temp);
	
	iterator->data = temp->data;
	
}

int SListIsEmpty(const slist_t *slist)
{
	/*returns 1 if they are equal */
	return (slist->head == slist->tail);
}

slist_iter_t SListRemove(slist_iter_t iterator)
{
	slist_iter_t replacement = NULL;


	if(NULL == iterator->next)
	{

		return iterator;
	}
	replacement = iterator->next;

	iterator->data = replacement->data;
	iterator->next = replacement->next;

	free(replacement);
	replacement = NULL;

	return iterator;


}



size_t SListCount(const slist_t *slist)
{
	size_t counter = 0;
	slist_iter_t temp = slist->head;
	assert(NULL != slist);

	printf("youre here\n");
	
	while(temp != slist->tail)
	{
		++counter;
		temp = temp->next;
		printf("%ld\n", counter);
	}
	return counter;
}

slist_iter_t SListBegin(const slist_t *slist)
{
	assert (NULL != slist);
	return slist->head;
}