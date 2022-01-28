#include <stdlib.h> /* strtod*/
#include <assert.h> /* assert */
#include <ctype.h> /* isspace, isdigit*/
#include <string.h> /* strchr */
#include <stdio.h>

#include "../../ds/include/bst.h"
#include "../../ds/include/queue.h"


#define HAS_RIGHT(node) (NULL != node->children[RIGHT])




enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

typedef struct bst_node bst_node_t;

struct bst_node
{
    void *data;
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
};

struct bst
{
    bst_node_t root_stub;
    bst_cmp_func_t CmpFunc;
};

int PrinterFunc(void *data, void *param);
int CompareData(const void *left, const void *right);
static bst_iter_t GetRoot(bst_t *tree);
void LevelBLevelPrint(bst_t *tree, queue_t *queue);




int main()
{
	bst_t *tree = BSTCreate(CompareData);
	queue_t *qt = QueueCreate();
   
    int data = 'A';
    int data1 = 'B';
    int data2 = 'C';
    int data3 = 'D';
    int data4 = 'E';

   	BSTInsert(tree, &data);
    BSTInsert(tree, &data1);
    BSTInsert(tree, &data2);
    BSTInsert(tree, &data3);
    BSTInsert(tree, &data4);

    
    LevelBLevelPrint(tree, qt);
    BSTForEach(BSTBegin(tree),BSTEnd(tree),PrinterFunc, BSTGetData(GetRoot(tree)) );

    BSTDestroy(tree);
    QueueDestroy(qt);

	return 0;
}

void LevelBLevelPrint(bst_t *tree, queue_t *queue)
{
	
	bst_node_t *runner = NULL;
	

	if (!BSTIsEmpty(tree))
	{
		QueueEnqueue(queue, tree->root_stub.children[LEFT]);
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
			printf("%c ,", *(char *)BSTGetData(runner));
			QueueDequeue(queue);
		}
		printf("\n");
	}

}


static bst_iter_t GetRoot(bst_t *tree)
{
	return tree->root_stub.children[LEFT];
}

int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}

int PrinterFunc(void *data, void *param)
{
   
    printf("BST Root %c ", (*(char*)param));
    printf("Node: %c\n", (*(char*)data));
    
   
    return 0;
}




