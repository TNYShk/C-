/**********************************\
* AVL   Test file                  *
* Developer:   Tanya               *
* Written: 2021-1-31               *
*                                  *
* Reviewer:                        *
\**********************************/
#include <stdio.h>    /* printf */
#include <assert.h> /* assert */

#include <stdlib.h> /*memory allocation & free */
#include <string.h> /* testing strlen, strcmp, strstr*/

#include "../include/avl.h"
#include "../include/queue.h"

typedef struct avl_node avl_node_t;

enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

struct avl_node
{
    void *data;
    size_t height; 
    avl_node_t *children[NUM_OF_CHILDREN];
};
struct avl
{
    avl_node_t *root;
    avl_cmp_func_t cmp_func;
};


void Swap(avl_node_t **left, avl_node_t **right);
void MirrorTree(avl_node_t* root);
int CompareData(const void *left, const void *right);

int PrintNodes(void *data, void *param);
int PrintChars(void *data, void *param);
int DontPrintNodes(void *data, void *param);
void LevelBLevelPrint(avl_t *tree, queue_t *queue);
void PrintTreeNicely(avl_t *avl);
static void PrintNicely(avl_node_t *node, int index);


void CreateDestroy();
void SizeHeight();
void FoolingAround();

int main(void)
{

	
	SizeHeight();
	CreateDestroy();
	FoolingAround();

	return 0;
}

void CreateDestroy()
{

	avl_t *avl = NULL;

	avl_t *avl1 = NULL;
	queue_t *qt = QueueCreate();
	int num = 6;
	int num2 = 18;
	int num3 = 5;
	int num4 = 4;
	int num5 = 11;
	int num6 = 99;
	int num7 = 100;
	printf("\n\tInsert & Remove  Tests\n");	
	
	avl1 = AVLCreate(CompareData);

	AVLDestroy(avl1);
	
	

	avl = AVLCreate(CompareData);
	assert(1 == AVLIsEmpty(avl));
	(0 == AVLInsert(avl, &num)? printf("inserted data into tree!\n"): printf("Failed!\n") );
	assert(0 == AVLInsert(avl, &num2));
	assert(0 == AVLIsEmpty(avl));
	/*assert(0 != AVLInsert(avl, &num2)); WORKS, assert same number */
	assert(0 == AVLInsert(avl, &num3));
	printf("\nTree height is %ld, inserting nodes\n\n", AVLHeight(avl));
	assert(0 == AVLInsert(avl, &num4));
	assert(0 == AVLInsert(avl, &num5));
	assert(0 == AVLInsert(avl, &num6));
	assert(6 == AVLSize(avl));
	assert(0 == AVLForEach(avl, PrintNodes, &num, IN_ORDER));
	printf("\nTree has %ld nodes\n",AVLSize(avl) );
	assert(3 == AVLHeight(avl));
	PrintTreeNicely(avl);
	printf("\n");
	printf("Emptying Tree!\n");
	AVLRemove(avl, &num6);
	AVLRemove(avl, &num4);
	AVLRemove(avl, &num5);
	AVLRemove(avl, &num7);
	AVLRemove(avl, &num2);
	AVLRemove(avl, &num3);
	AVLRemove(avl, &num);
	printf("\npost removal - size of tree is %ld\n",AVLSize(avl) );
	printf("\npost removal - tree height is %ld\n", AVLHeight(avl));
	assert(1 == AVLIsEmpty(avl));
	printf("\n\tCreate & Destroy & IsEmpty PASSED\n");
	
	printf("\ninserting nodes back! in dif order\n");
	
	assert(0 == AVLInsert(avl, &num2));
	assert(0 == AVLInsert(avl, &num3));
	assert(0 == AVLInsert(avl, &num4));
	assert(0 == AVLInsert(avl, &num5));
	assert(0 == AVLInsert(avl, &num6));
	assert(0 == AVLInsert(avl, &num));
	PrintTreeNicely(avl);
	printf("\n");
	LevelBLevelPrint(avl,qt);
	printf("\n");
	printf("removing nodes:\n");
	AVLRemove(avl, &num4);
	AVLRemove(avl, &num);
	AVLRemove(avl, &num3);
	
	PrintTreeNicely(avl);
	printf("\nIn Order Print:\n");
	assert(0 == AVLForEach(avl, PrintNodes, &num2, IN_ORDER));
	printf("\n");
	printf("\nPre Order Print:\n");
	assert(0 == AVLForEach(avl, PrintNodes, &num2, PRE_ORDER));
	printf("\nPost Order Print:\n");
	assert(0 == AVLForEach(avl, PrintNodes, &num2, POST_ORDER));
	
	printf("\nPrint by Level:\n");
	LevelBLevelPrint(avl,qt);
	QueueDestroy(qt);

	printf("\n");
	printf("\nStop Print Check:\n");
	assert(1 == AVLForEach(avl, DontPrintNodes, &num2, IN_ORDER));
	printf("\n");
	
	printf("\n");
	
	AVLDestroy(avl);

	printf("\n\tForEach Print Tests PASSED\n");

}

void SizeHeight()
{
	avl_t *avl = NULL;
	queue_t *qt = QueueCreate();
	int num = 16;
	int num2 = 18;
	int num3 = 5;
	int num4 = 10;
	int num5 = 11;
	int num6 = 12;
	int num7 = 118;
	printf("\n");
	printf("\n\tBST- rec size & Height Tests\n");

	avl = AVLCreate(CompareData);
	

	assert(1 == AVLIsEmpty(avl));
	
	(0 == AVLInsert(avl, &num)? printf("inserting data int tree!\n"): printf("Failed!\n") );
	assert(1 == AVLHeight(avl));
	assert(1 == AVLSize(avl));
	assert(0 == AVLInsert(avl, &num2));
	assert(0 == AVLInsert(avl, &num3));
	assert(0 == AVLInsert(avl, &num4));
	assert(0 == AVLInsert(avl, &num5));
	
	
	
	printf("\nPrint In order:\n");
	assert(0 == AVLForEach(avl, PrintNodes, &num, IN_ORDER));
	printf("\n");
	printf("\nprint by level:\n");
	LevelBLevelPrint(avl,qt);
	printf("\n\tAVLFind Tests\n");
	assert(NULL == AVLFind(avl,&num7));
	
	
	assert(0 == AVLInsert(avl, &num6));
	assert(0 == AVLInsert(avl, &num7));
	printf("print by level:\n");
	LevelBLevelPrint(avl,qt);
	printf("\nPrint PRE order:\n");
	assert(0 == AVLForEach(avl, PrintNodes, &num, PRE_ORDER));
	printf("\n");
	assert(&num7 == AVLFind(avl,&num7));
	printf("height is %ld\n",AVLHeight(avl));
	printf("\tAVLFind PASSED\n");
	assert(7 == AVLSize(avl));
	PrintTreeNicely(avl);
	
	QueueDestroy(qt);
	AVLDestroy(avl);
	printf("\n\tTree Size & Height PASSED\n");
	
}

void FoolingAround()
{
	avl_t *avl = NULL;
	
	int root = 'T';
	int left = 'A';
	int right = 'N';
	int left1 = 'Y';
	int right1 = 'a';
	int blank = ' ';
	avl = AVLCreate(CompareData);
	
	assert(0 == AVLInsert(avl, &root));
	assert(0 == AVLInsert(avl, &left));
	assert(0 == AVLInsert(avl, &right));
	assert(0 == AVLInsert(avl, &left1));
	assert(0 == AVLInsert(avl, &right1));
	printf("\n\tFooling Around Test\n");
	printf("\n");
	printf("\nTree data in-order Print:\n");
	
	AVLForEach(avl, PrintChars,&blank,PRE_ORDER);
	printf("\n");
	printf("\n");
	
	AVLDestroy(avl);
	
}



int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}


int PrintNodes(void *data, void *param)
{
	printf("Node: %d ", (*(int*)data));

	(void)param;

	 return 0;
}

int PrintChars(void *data, void *param)
{
	printf(" %c ", (*(char*)data));

	(void)param;

	 return 0;
}

int DontPrintNodes(void *data, void *param)
{
	 printf("Root: %d \n", (*(int*)param));
	 printf("Node: %d ", (*(int*)data));
	 
	 return -1;
}

void LevelBLevelPrint(avl_t *tree, queue_t *queue)
{
	
	avl_node_t *runner = NULL;
	

	if (!AVLIsEmpty(tree))
	{
		QueueEnqueue(queue, tree->root);
		while (!QueueIsEmpty(queue))
		{
			runner = QueuePeek(queue);
			if (NULL != runner->children[LEFT])
			{
				QueueEnqueue(queue, runner->children[LEFT]);
			}
			if (NULL != runner->children[RIGHT])
			{
				QueueEnqueue(queue, runner->children[RIGHT]);
			}
			printf("%d ", *(int *)runner->data);
			QueueDequeue(queue);
		}
		printf("\n");
	}

}

void PrintTreeNicely(avl_t *avl)
{
    PrintNicely(avl->root, 0);
}

static void PrintNicely(avl_node_t *node, int index)
{
    int i = 0;
    
    if (NULL == node)
    {
        return;
    }

    index += 10;
   
    PrintNicely(node->children[RIGHT], index);
   
    for (i = 10; i < index; ++i)
    {
        printf(" ");
    	
    }
   
    printf("%d\n", *(int *)node->data);

    PrintNicely(node->children[LEFT], index);
}

