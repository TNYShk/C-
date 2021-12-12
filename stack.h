#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h> /* size_t */

typedef struct stack stack_t; 

	
	

/* DESCRIPTION: 
 * create a stack based on given parameters
 *allocate memory according to params
 *
 * PARAMS: 
 * total number of elements requested by the user
 * element_size, maximum size of each element that can be passed by the user
 *	at the end of use call for StackDestroy
 * RETURN:
 * stack_t *ptr to the created stack,
 * NULL in case of failure
 */
stack_t *StackCreate(size_t num_of_elements, size_t element_size);


/* DESCRIPTION: 
 * push element on to top of the stack
 *	the user is responsible for knowing the stack capacity. and should
 * PARAMS: 
 * stack_t *ptr to the stack
 * const void *ptr of the element to push onto the stack
 *
 * RETURN:
 * no return value, 
 */
void StackPush(stack_t *sptr, const void *element);


/* DESCRIPTION: 
 * checks if stack_t is empty
 * 
 *
 * PARAMS: 
 * stack_t *ptr to the stack
 * 
 *
 * RETURN:
 * boolean for empty or not, 1 is true (empty)
 */
int StackIsEmpty(const stack_t *sptr);


/* DESCRIPTION: 
 * perform free for the allocated memory of the stack
 *	must be called at the end of the program (user's responsibility)
 * PARAMS: 
 * stack_t *ptr to struct to be destroyed

 * 
 * RETURN:
 * none, cant fail
 */
void StackDestroy(stack_t *sptr);


/* DESCRIPTION: 
 * checks how many elements are occupied
 * 
 *
 * PARAMS: 
 * stack_t *ptr to struct 
 * 
 *
 * RETURN:
 * return number of occupied elements of the stack
 */
size_t StackSize(const stack_t *sptr);


/* DESCRIPTION: 
 * peek to the top element of the stack, 
 *user shpuld check if the stack is empty before peeking
 * 
 * PARAMS: 
 * stack_t *ptr to the stack
 * 
 * WARNING: 
 * dinamically allocated copy, must be destroyed
 *
 * RETURN:
 * void *ptr to the copy of the top element, iy stack is empty returns NULL
 */
void *StackPeek(const stack_t *sptr);



/* DESCRIPTION: 
 * pops out the top element of the stack
 * user responsibility to check size of stack before popping 
 
 * PARAMS: 
 * stack_t *ptr to the stack
 * 
 *
 * RETURN:
 * no return value,
 */
void StackPop(stack_t *sptr);



/* DESCRIPTION: 
 * checks total zise of stack
 * 
 *
 * PARAMS: 
 * stack_t *ptr to stack 
 * 
 *
 * RETURN:
 * total size of stack
 */
size_t StackCapacity(const stack_t *sptr);



#endif /* __BIT_ARRAY_H__ */
