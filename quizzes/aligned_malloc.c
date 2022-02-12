#include <stdlib.h> /* size_t  */
#include <assert.h> /* asserts */
#include <stdio.h> /* printf */

#include <string.h>

#include "../ds/include/utils.h"

void *AlignedMalloc(size_t bytes, size_t align);
void AlignedFree(void *ptr);



int main (void)
{
    int *arr = AlignedMalloc(128,12);
    if (NULL == arr)
    {
        printf("Function Error!\n");
        return 1;
    }
   
    AlignedFree(arr);
  
   CONDITION_TEST(8,sizeof(arr));
    
    return 0;
}



void AlignedFree(void *ptr)
{
    free(*((void**)ptr -1));
    

}

void *AlignedMalloc(size_t bytes, size_t align)
{
    void *malloc_ptr = NULL;
    void *align_ptr = NULL;
    size_t header = sizeof(void *) + bytes + align;

    assert(bytes > 1);

    malloc_ptr = (void *)malloc(header);
    if(NULL == malloc_ptr)
    {
        return NULL;
    }
    header = (size_t)malloc_ptr + align + sizeof(void *);

    align_ptr = (void*)(header & -align);

    *((void**)align_ptr -1) = malloc_ptr;

    return align_ptr;
}