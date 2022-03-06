/***********************************
 * Semaphore_posix - Source File   *
 * Developer: Tanya                *
 *          Feb 25, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/
#include <fcntl.h>  /* O_* const.*/
#include <sys/stat.h> /* mode const. */
#include <semaphore.h> /*semaphore */
#include <stdio.h> /* printf*/
#include <pthread.h> /* threads.. */
#include <assert.h> /* assert*/
#include <unistd.h> /* sleep */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <string.h> /*strcmp */
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define atomic_sync_fetch_or(destptr, flag) __sync_fetch_and_or(destptr, flag)
#include "semaphore_posix.h" /* header */



#define FAIL (-1)
#define GREAT_SUCCESS (0)
#define SEMNAME (10)

static int curr_process_sem_val_g = 0; 
static char name_g[SEMNAME] = {'\0'};
static unsigned int flag_g;




sem_t *InitSemaphore(const char *name, int init_num, int DoU)
{
    sem_t *semP = NULL;

    strcpy(name_g, name);
    flag_g = DoU;

    semP =  sem_open(name, O_CREAT, S_IRUSR | S_IWUSR, init_num);
    if(SEM_FAILED == semP)
    {
        errExit("sem_open");
    }

    return semP;
}




int DoExit(sem_t *sem)
{
   if (flag_g)
   {
        if (0 < curr_process_sem_val_g)
        {   
            DoDecrement(sem, curr_process_sem_val_g);
        }
        else 
        {
            DoIncrement(sem, (-1 * curr_process_sem_val_g));
        }
    }
    
    if(FAIL == sem_close(sem))
        errExit("sem_close");
   
   
    system(" ls -al /dev/shm/sem.* | more ");
    return GREAT_SUCCESS;
}

int DoView(sem_t *sem)
{
    int value = 0;
   
    if(FAIL == sem_getvalue(sem, &value))
        errExit("sem_getvalue");

    system(" ls -al /dev/shm/sem.*|more ");
    return value;
}

int DoUnlink(sem_t *sem)
{
    if(FAIL == sem_unlink(name_g))
        errExit("sem_unlink");
     if(FAIL == sem_close(sem))
        errExit("sem_close");
   
    return GREAT_SUCCESS;
}



int DoDecrement(sem_t *sem, unsigned int val)
{
    size_t idx = 0;

    if (flag_g == 1)
    {
        curr_process_sem_val_g -= val; 
    }

    for(; idx <  val; ++idx)
    {
        if(EAGAIN == sem_wait(sem))
        errExit("sem_trywait");
    }

    system(" ls -al /dev/shm/sem.*|more ");
    return GREAT_SUCCESS;
}

int DoIncrement(sem_t *sem, unsigned int val)
{
    size_t idx = 0;

    if(flag_g == 1)
    {
        curr_process_sem_val_g += val;
    }

    for(; idx <  val; ++idx)
    {
        if( FAIL == sem_post(sem) )
            errExit("sem_post");
    }
    

   
    return GREAT_SUCCESS;
}

