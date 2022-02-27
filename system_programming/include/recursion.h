/**********************************\
* RECURSION                        *
* Developer:                       *
* Written: 2021-1-25               *
*                                  *
* Reviewer:                        *
\**********************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h> /* size_t */

#include "stack.h"

typedef struct node
{
    void *data;
    struct node *next;
}node_t;

/*
 * DESCRIPTION: 
 * Calculates the value of Fibonacci number of the requested index
 * 
 *
 *
 * PARAMS: 
 * index of desired Fib element
 * 
 * RETURN: value of the Fibonacci index
 *
 * O(n^2) time, O(tree height) memory */
int RecFibonacci(int element_index);
/*
 * DESCRIPTION: 
 * Calculates the value of Fibonacci number of the requested index
 * 
 * 
 *
 * PARAMS: Nada
 * 
 * RETURN: Pointer to the newly created dll, otherwise NULL
 * O(n) time, O(1) memory */
int IterFibonacci(int element_index);
/*
 * DESCRIPTION: 
 * Creates a new Double Linked List ("dll")
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: Nada
 * 
 * RETURN: Pointer to the newly created dll, otherwise NULL
 * O(n) time, O(n) memory */
node_t *RecFlipList(node_t *node);
/*
 * DESCRIPTION: 
 * Creates a new Double Linked List ("dll")
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: Nada
 * 
 * RETURN: Pointer to the newly created dll, otherwise NULL
 * O(n^2) time, O(n) memory */
void RecSort(stack_t *stack);

size_t RecStrLen(const char *str);

int RecStrCmp(const char *s1, const char *s2);

char *RecStrCpy(char *dest, const char *src);

char *RecStrCat(char *dest, const char *src);

char *RecStrStr(const char *haystack, const char *needle);


#endif /* __RECURSION_H__ */
