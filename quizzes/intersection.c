#include <stdlib.h> /* size_t, dyncamic memory allocation  */
#include <assert.h> /* asserts */
#include <string.h> /* memcpy*/
#include <stdio.h> /* printf */

typedef struct node
{
	void *data;
	struct node *next;
}node_t;

static size_t countElements(node_t *head);
static void MoveHead(node_t *head, size_t bymuch);
int VerifyIntersection(node_t *head_1, node_t *head_2);
int HasLoop(const node_t *head);


int main()
{
	int answer = -1;
	
	int x = 1;
	int y = 2;
	int z = 333;
	int w = 4;
	int t = 26;
	int tt = 265;
	node_t *head = NULL;
	node_t *head2 = NULL;
	node_t *temp = NULL;
	
	
	
	/*structs list 1 */
	node_t one;
	node_t two; 
	node_t three; 
	node_t four; 
	node_t five; 
	node_t onew;
	node_t twow; 
	
	one.data = &x;
	one.next = &two;
	two.data = &y;
	two.next = &three;
	three.data = &z;
	three.next = &four;
	four.data = &w;
	four.next = &five;
	five.data = &tt;
	five.next = NULL;

	onew.data = &t;
	onew.next = &twow;
	twow.data = &w;
	twow.next = &three;
	
	head = &one;
	head2 = &onew;
	


	
	
	answer = VerifyIntersection(head, head2);
	(answer == 0)? printf("no intersection\n") : printf("intersection at %d\n",answer);

	return 0;
}




int VerifyIntersection(node_t *head_1, node_t *head_2)
{
	node_t *run1 = head_1;
	node_t *run2 = head_2;

	int count1 = 0;
	int count2 = 0;
	int delta = 0;
	int answer = 0;

	assert (NULL != head_1);
	assert (NULL != head_2);
	
	count1 = countElements(run1);
	count2 = countElements(run2);

	delta = count1 - count2;

	if (0 > delta)
	{
		delta = -delta;
		MoveHead(run2, delta);
	}
	else
	{
		MoveHead(run1, delta);
	}
	count1 = countElements(run1);
	count2 = countElements(run2);

	while( (run1 != run2) && (run1->next != NULL) && (run2->next != NULL))
	{
		run1 = run1->next;
		run2 = run2->next;
		++answer;
	}
	
	return count2 - answer;
}


static size_t countElements(node_t *head2check)
{
	size_t counter = 0;

	assert(NULL != head2check);

	while (NULL != head2check->next)
	{
		++counter;
		head2check = head2check->next;
	}
	return counter;
}

static void MoveHead(node_t *head, size_t delta)	
{
	while(delta)
	{
		head = head->next;
		--delta;
	}
}

int HasLoop(const node_t *head)
{
	const node_t *turtois = head;
	const node_t *rabit = head;

	assert (NULL != head);

	do
	{
		turtois = turtois->next;
		rabit = rabit->next->next;
	}
	while ((turtois != rabit) && (NULL != rabit));

	return (turtois == rabit);

}