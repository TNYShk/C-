#include <assert.h> /* asserts */
#include <stdio.h> /* printf */




typedef struct node
{
	void *data;
	struct node *next;
}node_t;


node_t *FlipGetElem(node_t *head, int);


static size_t countElements(node_t *head);


int main()
{
	int x = 1;
	int y = 2;
	int z = 3;
	int w = 4;
	int t = 26;


	node_t *head = NULL;

	node_t *temp = NULL;
	
	
	/*structs list 1 */
	node_t one;
	node_t two; 
	node_t three; 
	node_t four; 
	node_t five; 	

	
	

	one.data = &x;
	one.next = &two;

	two.data = &y;
	two.next = &three;
	three.data = &z;
	three.next = &four;
	four.data = &w;
	four.next = &five;
	five.data = &t;
	five.next = NULL;
	
	head = &one;


	printf("\n\t----------------------------flip-------------------------------------------\n");
	
	printf("before flip data in one.next->data is %d\n", *(int *)one.next->data);
	printf("before flip data in two.next->data is %d\n", *(int *)two.next->data);
	printf("data in three.next->data (four) is %d\n", *(int *)three.next->data);
	printf("data in four.next->data (five) is %d\n", *(int *)four.next->data);
	temp = head;
	FlipGetElem(temp, 3);
	/*printf("nth element from the end hods val: %d\n",  *(int *)temp->data);
	printf("nth element from the end hods val: %d\n",  *(int *)head->data);
	
	printf("post flip data in two.next->data is %d\n", *(int *)two.next->data);
	printf("post flip data in three.next->data is %d\n", *(int *)three.next->data);
	printf("post flip data in four.next->data is %d\n", *(int *)four.next->data);
	*/

return 0;
	
}



node_t *FlipGetElem(node_t *head, int n)
{
	node_t *temp = NULL, *new_head = NULL, *prev_head = NULL;

	assert (NULL != head);

	prev_head = head;
	temp = prev_head;
	new_head = temp->next;

	while (NULL != new_head)
	{
		temp = new_head;
		new_head = temp->next;
		temp->next = prev_head;
		prev_head = temp;

	}
	head->next = NULL;

	while (n && (temp != NULL) )
	{
		--n;
		temp = temp->next;
		
	}
	printf("nth element from the end hods val: %d\n",  *(int *)temp->data);
	return temp;
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

