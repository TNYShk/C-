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


int main(void)
{
	avl_t *avl = NULL;
	int num = 10;
	avl = AVLCreate(CompareData);

	(1 == AVLIsEmpty(avl)? printf("empty tree!\n"): printf("NOT empty tree!\n") ); 

	(0 == AVLInsert(avl, &num)? printf("inserted data tree!\n"): printf("Failed!\n") ); 
	
	/*(1 == AVLIsEmpty(avl)? printf("empty tree!\n"): printf("NOT empty tree!\n") ); */
	printf("tree height is %ld\n", AVLHeight(avl));
	AVLDestroy(avl);
	/*(1 == AVLIsEmpty(avl)? printf("empty tree!\n"): printf("NOT empty tree!\n") ); */
	return 0;
}


int CompareData(const void *left, const void *right)
{
    return (*(size_t *)left - *(size_t *)right);
}