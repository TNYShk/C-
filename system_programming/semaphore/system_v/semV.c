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
#include <errno.h> /* errno*/
#include <signal.h> 
#include <string.h> /*strcmp */
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#include "semaphore_sys_v.h"
#define FILE_NAME ("/semaphore_sys_v.h")
#define FAIL_SEMA (-1)

#define LAZY_ASCII (128)
#define FAIL (-1)
#define INVALID_INPUT (1)
#define OK_EXIT (2)
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
static int IncrementSema(int  , int  , int );
static int GetSemaid(const unsigned char id, int value);
static void InitSemAct(void);
static int DoExit(int semid, char command);
static int DoNothing(int semid, char command);
static int DoView(int semid, char command);
static int DoUnlink(int semid, char command);
static int DoDecrement(int semid, char command);
static int DoIncrement(int semid, char command);




int main(int argc, const char *argv[])
{
    SysVSemManipulation(argv);
    (void)argc;
    return 0;
}






int SysVSemManipulation(const char **cmd)
{
    int semid = 0;
    int charly = ' ';
    int status = SUCCESS;
    assert(NULL != cmd[1]);
    assert(NULL != cmd[2]);

    semid = GetSemaid(atoi(cmd[1]),atoi(cmd[2]));
    if (FAIL_SEMA == semid)
    {
        errExit("semget");
    }

    InitSemAct();

    printf("please enter letter: I,D,V,R or X\n");
    while((charly != 'X') && (status != OK_EXIT))
    {
        charly = getc(stdin);
        status = sem_actions[charly](semid, charly);
    }
    return status;
}


static int GetSemaid(const unsigned char id, int value)
{
    key_t sema_key = 0;
    int sema_id = 0;

    char cwd[LAZY_ASCII] = {0};

    if (getcwd(cwd, sizeof(cwd)) == NULL) 
    {
        return EXIT_FAILURE; 
    }

    strcat(cwd,FILE_NAME);
    
    sema_key = ftok(cwd , id);
    if(FAIL == sema_key)
    {
        errExit("key_failed");
    }

    sema_id = semget(sema_key, value , IPC_CREAT | IPC_EXCL | 0666); 
    if (errno == EEXIST)
    {
        sema_id = semget(sema_key, value , 0);
    }
    else
    {
        IncrementSema(sema_id , value ,0);
    }

    return sema_id;
}




static void InitSemAct(void)
{
    size_t counter = 0;
    for(;counter < LAZY_ASCII; ++counter)
    {
        sem_actions[counter] = &DoNothing;
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
    return OK_EXIT;
}


static int DoNothing(int semid, char command)
{
    (void)semid;
    (void)command;
    return INVALID_INPUT;
}


static int DoView(int semid, char command)
{
    int value = 0;
    value = semctl(semid, 0, GETVAL);
    if(FAIL_SEMA == value)
        errExit("sem value");
    printf("Semaphore value is: %d\n", value);
    
    (void)command;

    return SUCCESS;

}

static int IncrementSema(int sema_id , int incrent_by , int undo_flag)
{
    struct sembuf op_settings = {0};

    assert(incrent_by >= 0);

    op_settings.sem_op = incrent_by;
    op_settings.sem_flg = 0;
    op_settings.sem_num = 0;

    if (undo_flag)
    {
        op_settings.sem_flg = SEM_UNDO;
    }
    
    return (FAIL_SEMA == semop(sema_id , &op_settings ,1)) ? EXIT_FAILURE : EXIT_SUCCESS ;
}



static int DoIncrement(int semid, char command)
{
    struct sembuf sem_opr = {0};
    printf("for UNDO presss u\n");
    command = getc(stdin);
    if (command == 'u')
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
    if (command == 'u')
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
    return OK_EXIT;
}


