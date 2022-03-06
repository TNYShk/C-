#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */
#include "semaphore_sys_v.h"  /* sys v semaphore API */
#define FAIL (-1)
#define SUCCESS (0)

int main(void)
{
 
    int sem_id = InitSem(8);

   printf("val is %d\n", SemGetVal(sem_id));

    assert(SUCCESS == SemIncrement(sem_id, 2));
     printf("val is %d\n", SemGetVal(sem_id));
   
    /*value will be 10*/

    assert(SUCCESS == SemDecrement(sem_id, 3));

    
    printf("val is %d\n", SemGetVal(sem_id));
    /*value will be 7*/
    SemRemove(sem_id);
    
    return 0;
}
