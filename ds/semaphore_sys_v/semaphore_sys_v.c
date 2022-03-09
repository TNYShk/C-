#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <pthread.h> /* threads.. */
#include <assert.h> /* assert*/
#include <unistd.h> /* sleep */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno*/
#include <signal.h> 
#include <string.h> /*strcmp */

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#include "semaphore_sys_v.h" /* sys v semaphore API */

#define FAIL (-1)
#define SUCCESS (0)


union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};



int InitSem( size_t init_val)
{
    int sem_id = 0;
    int proj_id = 0;
    union semun arg;

    key_t sema_key = ftok("../include/semaphore_sys_v.h" , proj_id);
    if(FAIL == sema_key)
    {
        errExit("key_failed");
    }

            
    sem_id = semget(sema_key, 1, 0666 | IPC_CREAT);
    if (FAIL == sem_id)
    {
         errExit("semget");
    }

    if(0 != init_val)
    {    
       
        arg.val = init_val;
        if (FAIL == semctl(sem_id, 0, SETVAL, arg))
        {
            errExit("semctl");
        }
    }

    return sem_id;
}


int SemRemove(int sem_id)
{
    union semun arg;

    if(FAIL == semctl(sem_id, 0, IPC_RMID, arg))
    {
         errExit("semctl");
    }

    printf("Semaphore removed\n");
    return SUCCESS;
}

int SemIncrement(int sem_id, size_t inc_by)
{
    struct sembuf sem_opr = {0};
    sem_opr.sem_flg = SEM_UNDO;

    sem_opr.sem_num = 0;
    sem_opr.sem_op = inc_by;

   return (FAIL == semop(sem_id , &sem_opr ,1) ? EXIT_FAILURE : EXIT_SUCCESS );
    
}

int SemGetVal(int sem_id)
{
    union semun arg = {0};
    int value = 0;
    if(FAIL == (value = semctl(sem_id, 0, GETVAL, arg)))
    {
         errExit("semctl");
    }
    
    return semctl(sem_id, 0, GETVAL);
}

int SemDecrement(int sem_id, size_t dec_by)
{
    struct sembuf sem_opr = {0};
    sem_opr.sem_flg = SEM_UNDO;

    sem_opr.sem_num = 0;
    sem_opr.sem_op = -dec_by;


    return (FAIL == semop(sem_id, &sem_opr, 1) ? EXIT_FAILURE : EXIT_SUCCESS );
 
}
