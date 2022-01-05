#include <assert.h> /* asserts */
#include <stdio.h> /* printf */




typedef struct node
{
	void *data;
	struct node *next;
}node_t;


node_t *FlipGetElem(node_t *head, int);
node_t *GetNthfrmBack( node_t *head, size_t n);




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


	printf("before flip data in one.next->data is %d\n", *(int *)one.next->data);
	printf("before flip data in two.next->data is %d\n", *(int *)two.next->data);
	printf("data in three.next->data (four) is %d\n", *(int *)three.next->data);
	printf("data in four.next->data (five) is %d\n", *(int *)four.next->data);
	temp = GetNthfrmBack(head, 1);
	printf("\nnth element from last is %d\n", *(int *)temp->data);
	printf("\n\t-------------------------flipnget-------------------------------\n");
	temp = head;
	FlipGetElem(temp, 0);

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

	while (n && (temp->next != NULL) )
	{
		--n;
		temp = temp->next;
		printf("%dth element from the end holds val: %d\n",n,  *(int *)temp->data);
	}
	printf("nth element from the end holds val: %d\n",  *(int *)temp->data);
	return temp;
}

node_t *GetNthfrmBack(node_t *head, size_t nth)
{
	node_t *runner = head;

	assert (NULL != head);

	while(NULL != runner && nth)
	{
		--nth;
		runner = runner->next;
	}

	while(NULL != runner)
	{
		head = head->next;
		runner = runner->next;
	}
	return head;
}


