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


#define LAZY_LUT (128)
#define FAIL (-1)
#define GREAT_SUCCESS (0)
#define SEMNAME (10)

int curr_process_sem_val_g = 0; 
char name_g[SEMNAME] = {0}; 
static unsigned int flag_g = 0;

typedef int (*sem_act_func)(sem_t *sem, unsigned int val);
static sem_act_func sem_actions[LAZY_LUT] = {NULL};

static void InitSemAct(void);
static sem_t *InitSemaphore(const char **cmd);
static int DoExit(sem_t *sem, unsigned int val);
static int DoView(sem_t *sem, unsigned int val);
static int DoUnlink(sem_t *sem, unsigned int val);
static int DoDecrement(sem_t *sem, unsigned int val);
static int DoIncrement(sem_t *sem, unsigned int val);
static int DoNothing(sem_t *sem, unsigned int val);
static int DoU(sem_t *sem, unsigned int val);




static void InitSemAct(void)
{
    size_t idx = 0;
    for(; idx < LAZY_LUT; ++idx)
    {
        sem_actions[idx] = &DoNothing;
    }
    sem_actions['X'] = &DoExit;
    sem_actions['V'] = &DoView;
    sem_actions['I'] = &DoIncrement;
    sem_actions['D'] = &DoDecrement;
    sem_actions['R'] = &DoUnlink;
    sem_actions['U'] = &DoU;
  
}

static sem_t *InitSemaphore(const char **cmd)
{
    strcpy(name_g, cmd[1]);
    return sem_open(cmd[1], O_CREAT, S_IRUSR | S_IWUSR, atoi(cmd[2]));
}

int PosixSemManipulation(const char **cmd)
{
    sem_t *semP = NULL;
    semP = InitSemaphore(cmd);
    if(SEM_FAILED == semP)
    {
        errExit("sem_open");
    }

    InitSemAct();
   
    return sem_actions[(size_t)cmd[2][0]] (semP, atoi(cmd[2]));
}

static int DoNothing(sem_t *sem, unsigned int val)
{
    
    (void)val;
    if(FAIL == sem_close(sem))
        errExit("sem_close");

    system(" ls -al /dev/shm/sem.*|more ");
    return GREAT_SUCCESS;
}

static int DoExit(sem_t *sem, unsigned int val)
{
   if (flag_g)
   {
        if (0 < curr_process_sem_val_g)
        {   
            return DoDecrement(sem, curr_process_sem_val_g);
        }
        else 
        {
            return DoIncrement(sem, (-1 * curr_process_sem_val_g));
        }
    }
    
    if(FAIL == sem_close(sem))
        errExit("sem_close");
   
    (void)val;
    system(" ls -al /dev/shm/sem.* | more ");
    return GREAT_SUCCESS;
}

static int DoView(sem_t *sem, unsigned int val)
{
    int value = 0;
   
    if(FAIL == sem_getvalue(sem, &value))
        errExit("sem_getvalue");
    
    printf("getval view is %d\n", value);
    if(FAIL == sem_close(sem))
        errExit("sem_close");

    (void)val;
    system(" ls -al /dev/shm/sem.*|more ");
    return GREAT_SUCCESS;
}

static int DoUnlink(sem_t *sem, unsigned int val)
{
    if(FAIL == sem_unlink(name_g))
        errExit("sem_unlink");
    
    (void)val;
   
    return GREAT_SUCCESS;
}

static int DoU(sem_t *sem, unsigned int val)
{
    
    atomic_sync_fetch_or(&flag_g, 1); /* flag_g = 1;*/
    return DoExit(sem, val);
}

static int DoDecrement(sem_t *sem, unsigned int val)
{
    
    if( EAGAIN == sem_trywait(sem))
        errExit("sem_trywait");
   
    if (flag_g == 1)
    {
        curr_process_sem_val_g -= val;
        
    }
   
    if(FAIL == sem_close(sem))
        errExit("sem_close");

    system(" ls -al /dev/shm/sem.*|more ");
    return GREAT_SUCCESS;
}

static int DoIncrement(sem_t *sem, unsigned int val)
{
    if( FAIL == sem_post(sem) )
        errExit("sem_post");
    
    if(flag_g == 1)
    {
        curr_process_sem_val_g += 1;
        val = curr_process_sem_val_g;
        flag_g = 0;
    }
     
    if(FAIL == sem_close(sem))
        errExit("sem_close");

    system(" ls -al /dev/shm/sem.*|more ");
    return GREAT_SUCCESS;
}

