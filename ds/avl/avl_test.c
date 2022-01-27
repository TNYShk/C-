/**********************************\
* AVL   test file                *
* Developer:   Tanya               *
* Written: 2021-1-25               *
*                                  *
* Reviewer:                        *
\**********************************/
#include <stdio.h>    /* printf */
#include <assert.h> /* assert */
#include <math.h> /* power fabs */
#include <stdlib.h> /*memory allocation & free */
#include <string.h> /* testing strlen, strcmp, strstr*/

#include "avl.h"


int CompareData(const void *left, const void *right);
int PrintNodes(void *data, void *param);

int main(void)
{
	avl_t *avl = NULL;
	int num = 6;
	int num2 = 8;
	int num3 = 5;
	int num4 = 10;
	int num5 = 11;
	avl = AVLCreate(CompareData);
	
	(1 == AVLIsEmpty(avl)? printf("empty tree!\n"): printf("NOT empty tree!\n") ); 
	printf("node size is %ld\n",AVLSize(avl) );
	(0 == AVLInsert(avl, &num)? printf("inserted data tree!\n"): printf("Failed!\n") ); 
	(1 == AVLIsEmpty(avl)? printf("empty tree!\n"): printf("NOT empty tree!\n") );
	printf("size or tree is %ld\n",AVLSize(avl) );
	(0 == AVLInsert(avl, &num2)? printf("inserted data tree!\n"): printf("Failed!\n") ); 
	printf("tree height is %ld\n", AVLHeight(avl));
	printf("nodes in tree %ld\n",AVLSize(avl) );

	(1 == AVLIsEmpty(avl)? printf("empty tree!\n"): printf("NOT empty tree!\n") ); 
	(0 == AVLInsert(avl, &num3)? printf("inserted data tree!\n"): printf("Failed!\n") ); 
	printf("tree height is %ld\n", AVLHeight(avl));
	printf("size of tree is %ld\n",AVLSize(avl));
	(0 == AVLInsert(avl, &num4)? printf("inserted data tree!\n"): printf("Failed!\n") ); 
	printf("\ntree height is %ld\n", AVLHeight(avl));
	printf("size of tree is %ld\n",AVLSize(avl) );
	assert(NULL == AVLFind(avl, &num5));
	assert(&num4 == AVLFind(avl, &num4));
	(1 == AVLIsEmpty(avl)? printf("empty tree!\n"): printf("NOT empty tree!\n") );

	printf("\n Pre Order\n");
	AVLForEach(avl, PrintNodes, &num5,PRE_ORDER);
	printf("\n In Order\n");
	AVLForEach(avl, PrintNodes, &num5,IN_ORDER);
	printf("\n Post Order\n");
	AVLForEach(avl, PrintNodes, &num5,POST_ORDER);
	printf("\n \n");
	AVLDestroy(avl);
	
	/* */

	return 0;
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