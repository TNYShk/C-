#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct slist slist_t;
typedef struct slist_node* slist_iter_t; 

#include "sll.h"


struct slist_node
{
	 void *data;
	 struct slist_node *next;
}; 

struct slist /* the iterator, points to node ,slist_t*/
{
	struct slist_node *head;
};



slist_t *SListCreate(void)
{
	slist_t *slinky = (slist_t *)malloc(sizeof(slist_t));
	assert (NULL != slinky);

	slinky->head =  NULL;
	return slinky;

}

void SListDestroy(slist_t *slist)
{
	slist_iter_t current =  slist->head;
	slist_t temp =  slist;

	while (NULL != current)
	{
		temp = current->next;
		free(current->data);
		free(current);
		current = temp;
	}
	free(slist);
}



