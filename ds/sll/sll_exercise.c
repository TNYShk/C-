#include <stdlib.h> /* size_t, dyncamic memory allocation  */
#include <assert.h> /* asserts */
#include <string.h> /* memcpy*/
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


int main()
{
	int x = 1;
	int y = 2;
	int z = 333;
	int w = 4;
	int t = 26;
	int ans = -1;

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
	
	

	printf("\n\t--------------------------2 lists, check for loop--------------------------------\n");
	head = &one;
	ans = HasLoop(head);
	printf("list 1 is there a loop? zero for no: %d\n", ans);

	onew.data = &t;
	onew.next = &twow;
	twow.data = &w;
	twow.next = &onew;

	head2 = &onew;
	ans = HasLoop(head2);

	printf("list 2 is there a loop? zero for no: %d\n", ans);
	printf("\n\t--------------------------find intersection--------------------------------\n");
	twow.next = &three;
	temp = FindIntersection(head,head2);
	printf("check for intersection node, its value is: %d\n", *(int*)temp->data);

	printf("\n\t--------------------------flip--------------------------------------\n");
	printf("data in three.next->data is %d\n", *(int*)three.next->data);
	Flip(head);
	printf("post flip data in two.next->data is %d\n", *(int*)two.next->data);
	printf("post flip data in three.next->data is %d\n", *(int*)three.next->data);



return 0;
	
}



node_t *Flip(node_t *head)
{
	node_t *temp1 = NULL, *temp2 = NULL, *temp3 = NULL;

	assert (NULL != head);

	temp3 = head;
	temp1 = temp3;
	temp2 = temp1->next;

	while (NULL != temp2)
	{
		temp1 = temp2;
		temp2 = temp1->next;
		temp1->next = temp3;
		temp3 = temp1;

	}
	head->next = NULL;

	return temp2;
}

int HasLoop(const node_t *head)
{
	const node_t *temp1 = head;
	const node_t *temp2 = head;

	assert (NULL != head);

	do
	{
		temp1 = temp1->next;
		temp2 = temp2->next->next;
	}
	while ((temp1 != temp2) && (NULL != temp2));

	return (temp1 == temp2);

}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *temp1 = head_1;
	node_t *temp2 = head_2;

	int count1 = 0;
	int count2 = 0;
	int diff = 0;

	assert (NULL != head_1);
	assert (NULL != head_2);

	while(NULL != temp1->next)
	{
		++count1;
		temp1 = temp1->next;
	}
	temp1 = head_1;

	while(NULL != temp2->next)
	{
		++count2;
		temp2 = temp2->next;
	}
	temp2 = head_2;

	diff = count1 - count2;

	if (0 > diff)
	{
		diff = -diff;
		while (diff)
		{
			temp2 = temp2->next;
			--diff;
		}
	}
	else
	{
		while(diff)
		{
			temp1 = temp1->next;
			--diff;
		}
	}

	while( (temp1->next != NULL) || (temp2->next != NULL) )
	{
		if(temp1->next == temp2->next)
		{
			return temp1->next;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	return NULL;
}