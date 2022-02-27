/***********************************
 * Semaphore system V - Source File   *
 * Developer: Tanya                *
 *          Feb 25, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <pthread.h> /* threads.. */
#include <assert.h> /* assert*/
#include <unistd.h> /* sleep */
#include <stdlib.h> /* atoi */
#include <errno.h>
#include <signal.h>
#include <string.h> /*strcmp */
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#include "semaphore_sys_v.h"
#define FAIL (-1)
#define LAZY_ASCII (128)
#define EXIT (5)
#define SUCCESS (0)
typedef int (*sem_act_func)(int semid, char command);
static sem_act_func sem_actions[LAZY_ASCII] = {NULL};

union semun 
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
#if defined(__linux__)
    struct seminfo *__buf;
#endif
};


static void InitSemAct(void);
static int DoExit(int semid, char command);
static int DoView(int semid, char command);
static int DoUnlink(int semid, char command);
static int DoDecrement(int semid, char command);
static int DoIncrement(int semid, char command);

int main(int argc, const char *argv[])
{
    
    SysVSemManipulation(argv);
    return 0;
}


int SysVSemManipulation(const char **cmd)
{
    struct semid_ds ds ;
    union semun arg;
    int semid = 0, j = 0;
    int charly = ' ';
    int status = 0;
    key_t key = ftok(cmd[1], j);
    if(FAIL == key)
    {
        errExit("key_failed");
    }

    semid = semget(key, 1, IPC_CREAT);
    if(FAIL == semid)
    {
        errExit("semget");
    }

    arg.val = atoi(cmd[2]);
    if (FAIL == semctl(semid, 0, SETVAL, arg))
    {
        errExit("semctl");
    }
    InitSemAct();
    printf("please enter letter: I,D,V,R or X\n");
    while((charly != 'X') && (status != EXIT))
    {
        charly = getc(stdin);
        status = sem_actions[charly](semid, charly);
    }
    return status;
}

static void InitSemAct(void)
{
    size_t counter = 0;
    for(;counter < LAZY_ASCII; ++counter)
    {
        sem_actions[counter] = NULL;
    }
    sem_actions['X'] = &DoExit;
    sem_actions['V'] = &DoView;
    sem_actions['I'] = &DoIncrement;
    sem_actions['D'] = &DoDecrement;
    sem_actions['R'] = &DoUnlink;
    
}

static int DoExit(int semid, char command)
{
    (void)semid;
    (void)command;
    return EXIT;
}




static int DoView(int semid, char command)
{
    union semun arg = {0};
    printf("Semaphore value is: %d\n", semctl(semid, 0, GETVAL, arg));
    
    (void)command;

    return SUCCESS;

}

static int DoIncrement(int semid, char command)
{
    struct sembuf sem_opr = {0};
    printf("for UNDO presss u\n");
    command = getc(stdin);
    if (command = 'u')
    {
        sem_opr.sem_flg |= SEM_UNDO;
    }
    sem_opr.sem_num = 0;
    sem_opr.sem_op = 1;
    (void)command;

    return semop(semid, &sem_opr, 1);
}

static int DoDecrement(int semid, char command)
{
    struct sembuf sem_opr = {0};
    printf("for UNDO presss u\n");
    command = getc(stdin);
    if (command = 'u')
    {
        sem_opr.sem_flg |= SEM_UNDO;
    }
    sem_opr.sem_num = 0;
    sem_opr.sem_op = -1;
    (void)command;

    return semop(semid, &sem_opr, 1);
}


static int DoUnlink(int semid, char command)
{
    union semun arg;
    
    (void)command;
    if(FAIL == semctl(semid, 0, IPC_RMID, arg))
    {
        errExit("semctl_remove");
    }
    printf("removed?\n");
    return EXIT;
}


