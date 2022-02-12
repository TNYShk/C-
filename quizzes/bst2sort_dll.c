/**********************************
 * Quiz convert BST to sorted DLL *
 * Developer: Tanya               *
 * Feb 8, 2022                    *
 *                                *
***********************************/
#include <stdio.h> 

typedef struct node node_t;


enum children
{
	LEFT,
	RIGHT,
	NUM_CHILDREN
};

struct node
{
	void *data;
	node_t *children[NUM_CHILDREN];
};

static void PrintTree(node_t *node);
static void printList(node_t *node);
node_t *BSTtoSortelList(node_t *root);
static node_t newNode(void *data);

int main()
{
	node_t *head = NULL;

	int x4 = 1, x6 = 3, x8 = 5, x10 = 7, x12 = 9, x14 = 14, x16 = 16;
	void *data4 = &x4, *data6 = &x6, *data8 = &x8, *data10 = &x10, *data12 = &x12, *data14 = &x14, *data16 = &x16;

	node_t root = newNode(data4);
	node_t node1 = newNode(data6);
	node_t node2 = newNode(data8);
	node_t node3 = newNode(data10);
	node_t node4 = newNode(data12);
	node_t node5 = newNode(data14);
	node_t node6 = newNode(data16);
	
	
	node1.children[LEFT] = &root;
	node1.children[RIGHT] = &node2;
	node3.children[LEFT] = &node1;
	node3.children[RIGHT] = &node5;
	node5.children[LEFT] = &node4;
	node5.children[RIGHT] = &node6;

	printf("BST in order print:\n");
	PrintTree(&node3);
	printf("\n");
	
	head = BSTtoSortelList(&node3);
	
	while(head->children[LEFT] != NULL)
	{
		head = head->children[LEFT];
	}

	printList(head);
	printf("\n");
	return 0;
}



node_t *BSTtoSortelList(node_t *root)
{
	if(NULL == root)
	{
		return root;
	}

	if(NULL != root->children[LEFT])
	{
		node_t *left = BSTtoSortelList(root->children[LEFT]);

		while (NULL != left->children[RIGHT])
		{
			left = left->children[RIGHT];
		}
		left->children[RIGHT] = root;
		root->children[LEFT] = left;
	}

	if (NULL != root->children[RIGHT])
	{
		node_t *right = BSTtoSortelList(root->children[RIGHT]);

		while (NULL != right->children[LEFT])
		{
			right = right->children[LEFT];
		}

		right->children[LEFT] = root;
		root->children[RIGHT] = right;
	}
	return root;
}

static void printList(node_t *node)
{
	printf("As a list:\n");
    while (NULL != node)
    {
        printf("%d ", *(int *)node->data);
        node = node->children[RIGHT];
    }
}

static void PrintTree(node_t *node)
{
	if (NULL == node)
	{
		return;
	}
	
	PrintTree(node->children[LEFT]);
	
	printf("%d ", *(int *)node->data);
	
	PrintTree(node->children[RIGHT]);
}

static node_t newNode(void *data)
{
    node_t node = {0};
    node.data = data;
    node.children[LEFT] = NULL;
    node.children[RIGHT] = NULL;
    return node;
}