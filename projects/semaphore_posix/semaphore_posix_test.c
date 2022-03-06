/***********************************
 * Semaphore_posix - Source File   *
 * Developer: Tanya                *
 *          Feb 25, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/
#include <fcntl.h>  /* O_* const.*/
#include <sys/stat.h> /* mode const. */
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h> /* threads.. */
#include <assert.h> /* assert*/
#include <unistd.h> /* sleep */
#include <stdlib.h> /* atoi */
#include <errno.h>
#include <signal.h>
#include <stdlib.h> /* atoi */
#include "semaphore_posix.h"

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)



int main(void)
{

   
    sem_t *test = NULL;
     
    test = InitSemaphore("tny", 2, 0);
    
    printf("value is %d\n", DoView(test));

    DoIncrement(test,1);
    printf("value is %d\n", DoView(test));
    DoDecrement(test,2);
    printf("value is %d\n", DoView(test));

   
    DoUnlink(test);
     system(" ls -al /dev/shm/sem.* | more ");
    return 0;
}



