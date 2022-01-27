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
int DontPrintNodes(void *data, void *param);

void CreateDestroy();
void SizeHeight();


int main(void)
{
	avl_t *avl = NULL;
	int num = 6;
	int num2 = 8;
	int num3 = 5;
	int num4 = 10;
	int num5 = 11;

	CreateDestroy();
	SizeHeight();
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
	printf("\nForEach Tests: stops once status changes\n");
	printf("Pre Order\n");
	assert(1 == AVLForEach(avl, DontPrintNodes, &num, IN_ORDER));
	printf("\n In Order\n");
	AVLForEach(avl, PrintNodes, &num, PRE_ORDER );
	printf("\n Post Order\n");
	AVLForEach(avl, PrintNodes, &num,POST_ORDER);
	printf("\n \n");
	AVLDestroy(avl);
	
	

	return 0;
}

void CreateDestroy()
{

	avl_t *avl = NULL;
	avl_t *avl1 = NULL;
	int num = 6;
	int num2 = 18;
	int num3 = 5;
	int num4 = 10;
	int num5 = 11;
	int num6 = 110;

	printf("\n\tCreate & Destroy Tests\n");	
	avl1 = AVLCreate(CompareData);
	assert(1 == AVLIsEmpty(avl1));
	AVLDestroy(avl1);

	avl = AVLCreate(CompareData);
	assert(1 == AVLIsEmpty(avl));
	(0 == AVLInsert(avl, &num)? printf("inserted data tree!\n"): printf("Failed!\n") );
	assert(0 == AVLInsert(avl, &num2));
	/*assert(0 != AVLInsert(avl, &num2)); WORKS, assert same number */
	assert(0 == AVLInsert(avl, &num3));
	assert(0 == AVLInsert(avl, &num4));
	assert(0 == AVLInsert(avl, &num5));
	assert(0 == AVLInsert(avl, &num6));
	assert(6 == AVLSize(avl));
	assert(0 == AVLForEach(avl, PrintNodes, &num, IN_ORDER));
	AVLDestroy(avl);

	printf("\n\tCreate & Destroy & IsEmpty PASSED\n");

}

void SizeHeight()
{
	avl_t *avl = NULL;
	int num = 16;
	int num2 = 18;
	int num3 = 5;
	int num4 = 10;
	int num5 = 11;
	int num6 = 12;

	printf("\n\tBST- rec size & Height Tests\n");

	avl = AVLCreate(CompareData);
	assert(1 == AVLIsEmpty(avl));
	(0 == AVLInsert(avl, &num)? printf("inserting data int tree!\n"): printf("Failed!\n") );
	assert(1 == AVLHeight(avl));
	assert(1 == AVLSize(avl));
	assert(0 == AVLInsert(avl, &num2));
	assert(2 == AVLHeight(avl));
	assert(0 == AVLInsert(avl, &num3));
	assert(0 == AVLInsert(avl, &num4));
	assert(3 == AVLHeight(avl));
	
	assert(0 == AVLInsert(avl, &num5));
	assert(0 == AVLInsert(avl, &num6));
	assert(5 == AVLHeight(avl));
	assert(6 == AVLSize(avl));
	printf("\n");
	assert(0 == AVLForEach(avl, PrintNodes, &num, PRE_ORDER));
	printf("\n");
	assert(1 == AVLForEach(avl, DontPrintNodes, &num, IN_ORDER));
	printf("\n");
	assert(0 == AVLForEach(avl, PrintNodes, &num, POST_ORDER));
	printf("\n");
	AVLDestroy(avl);
	printf("\n\tTree Size & Height PASSED\n");
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

int DontPrintNodes(void *data, void *param)
{
	 printf("Root: %d \n", (*(int*)param));
	 printf("Node: %d ", (*(int*)data));
	 

	 return -1;
}

