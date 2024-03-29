#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h> /* size_t */

typedef struct stack stack_t; 


	

/* DESCRIPTION: 
 * create a stack based on user's parameters
 * allocate memory accordingly
 *
 * !at the end of use, call for StackDestroy() to free memory!
 *
 * PARAMS: 
 * num_of_elements - total number of elements requested by the user
 * element_size - maximum size for an element that can be passed by the user
 *	
 * RETURN:
 * stack_t *sptr to the created stack,
 * NULL in case of failure
 */
stack_t *StackCreate(size_t num_of_elements, size_t element_size);


/* DESCRIPTION: 
 * Push given element on to top of the stack.
 * !User is accountable for the stack capacity. If the size is exceeded the function behaviour is undefined.!
 * 
 * PARAMS: 
 * stack_t *sptr - to the stack
 * const void *element - the pointer to the element to push onto the stack
 *
 * RETURN:
 * no return value.
 */
void StackPush(stack_t *sptr, const void *element);


/* DESCRIPTION: 
 * checks if stack_t is empty
 * 
 *
 * PARAMS: 
 * const stack_t *sptr - pointer to the stack
 * 
 *
 * RETURN:
 * return 1 if empty, otherwise 0.
 */
int StackIsEmpty(const stack_t *sptr);


/* DESCRIPTION: 
 * perform free for the allocated memory of the stack
 *	must be called at the end of the stack usage 
 * 
 * PARAMS: 
 * stack_t *sptr - pointer to the stack to be destroyed
 *
 * 
 * RETURN:
 * no return value.
 */
void StackDestroy(stack_t *sptr);


/* DESCRIPTION: 
 * checks how many elements are occupied in stack_t.
 * 
 *
 * PARAMS: 
 * const stack_t *sptr - pointer to the stack 
 * 
 *
 * RETURN:
 * return number of the occupied elements
 */
size_t StackSize(const stack_t *sptr);


/* DESCRIPTION: 
 * peek to the top element of the stack, 
 * peeking at an empty stack causes undefined behaviour.
 * ! User is accountable for stack, and should be aware of its emptiness !
 *
 * PARAMS: 
 * const stack_t *sptr - pointer to the stack
 * 
 *
 * RETURN:
 * void *ptr to the top element.
 */
void *StackPeek(const stack_t *sptr);



/* DESCRIPTION: 
 * pops out the top element of the stack,
 * popping an empty stack causes undefined behaviour. 
 * ! User is accountable for stack, and should be aware of its emptiness !
 *
 * PARAMS: 
 * stack_t *sptr - pointer to the stack
 * 
 *
 * RETURN:
 * no return value.
 */
void StackPop(stack_t *sptr);



/* DESCRIPTION: 
 * checks total size of stack (capacity).
 * 
 *
 * PARAMS: 
 * const stack_t *sptr - pointer to stack 
 * 
 *
 * RETURN:
 * number of elements that can be stored.
 */
size_t StackCapacity(const stack_t *sptr);



#endif /* __STACK_H__ */
