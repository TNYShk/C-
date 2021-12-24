#include <assert.h> /* asserts */
#include <stdio.h> /* printf */

/* ********reviewed by Nurit *************/


typedef struct node
{
	void *data;
	struct node *next;
}node_t;


node_t *Flip(node_t *head);
int HasLoop(const node_t *head);
node_t *FindIntersection(node_t *head_1, node_t *head_2);

static size_t countElements(node_t *head);
static void MoveHead(node_t *head, size_t bymuch);

int main()
{
	int x = 1;
	int y = 2;
	int z = 333;
	int w = 4;
	int t = 26;


	node_t *head = NULL;
	node_t *head2 = NULL;
	node_t *temp = NULL;
	
	
	/*structs list 1 */
	node_t one;
	node_t two; 
	node_t three; 
	node_t four; 
	
	/*structs list 2 */
	node_t onew;
	node_t twow; 
	
	

	one.data = &x;
	one.next = &two;

	two.data = &y;
	two.next = &three;
	three.data = &z;
	three.next = &four;
	four.data = &w;
	four.next = NULL;
	
	

	printf("\n\t--------------------------2 lists, check for loop---------------------------\n");
	head = &one;
	
	( (0 == HasLoop(head)) ? printf("List1 No Loop here\n") : printf("List1 Found Loop\n") );
	
	onew.data = &t;
	onew.next = &twow;
	twow.data = &w;
	twow.next = &onew;

	head2 = &onew;
	( (0 == HasLoop(head2)) ? printf("List2 No Loop here\n") : printf("List2 Found Loop\n") );
	
	printf("\n\t--------------------------find intersection--------------------------------\n");
	twow.next = &three;
	temp = FindIntersection(head,head2);
	printf("\ncheck for intersection node, its value is: %d\n", *(int *)temp->data);

	printf("\n\t----------------------------flip-------------------------------------------\n");
	printf("data in three.next->data is %d\n", *(int *)three.next->data);
	Flip(head);
	printf("post flip data in two.next->data is %d\n", *(int *)two.next->data);
	printf("post flip data in three.next->data is %d\n", *(int *)three.next->data);



return 0;
	
}



node_t *Flip(node_t *head)
{
	node_t *temp1 = NULL, *new_head = NULL, *prev_head = NULL;

	assert (NULL != head);

	prev_head = head;
	temp1 = prev_head;
	new_head = temp1->next;

	while (NULL != new_head)
	{
		temp1 = new_head;
		new_head = temp1->next;
		temp1->next = prev_head;
		prev_head = temp1;

	}
	head->next = NULL;

	return new_head;
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
	while ( (turtois != rabit) && (NULL != rabit) );

	return (turtois == rabit);
}


node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *run1 = head_1;
	node_t *run2 = head_2;

	int count1 = 0;
	int count2 = 0;
	int delta = 0;

	assert (NULL != head_1);
	assert (NULL != head_2);
	count1 = countElements(head_1);
	count2 = countElements(head_2);
	

	count1 = countElements(run1);
	run1 = head_1;

	count2 = countElements(run2);
	run2 = head_2;

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
	
	while( (run1->next != NULL) || (run2->next != NULL) )
	{
		if(run1->next == run2->next)
		{
			return run1->next;
		}
		run1 = run1->next;
		run2 = run2->next;
	}
	return NULL;
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