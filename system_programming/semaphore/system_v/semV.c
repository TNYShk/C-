#include <sys/types.h>  /* key_t           */
#include <sys/ipc.h>    /* ftok            */
#include <sys/sem.h>    /* sys V semaphore */
#include <stdio.h>      /* printf          */
#include <stdlib.h>     /* atoi            */
#include <string.h>     /* strtok          */
#include <errno.h>      /* errno           */


#include "semaphore_sys_v.h"

#define MAX_INPUT (4096)
#define TRUE      (1)
#define FALSE     (0)
#define LUT_SIZE  (256)
#define SPACE     (" ")
#define EXIT_CHAR ("X\n")
#define UNDO_FLAG ('U')

typedef enum status
{
    FAILURE = -1,
    SUCCESS = 0,
    INVALID_INPUT = 1,
    OK_EXIT = 2
} sem_status_t;

enum arg_arr_vals
{
    COMMAND,
    SEM_ID,
    NUM,
    OPTION
};

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

/* LUT functions */
typedef sem_status_t (*sem_oper_func)(int sem_id, char *args_arr);

static sem_status_t  SemDecrement  (int sem_id, char *args_arr);
static sem_status_t  SemIncrement  (int sem_id, char *args_arr);
static sem_status_t  SemGetVal     (int sem_id, char *args_arr);
static sem_status_t  SemRemove     (int sem_id, char *args_arr);
static sem_status_t  SemInvalid    (int sem_id, char *args_arr);
static sem_status_t  SemExit       (int sem_id, char *args_arr);
static sem_status_t  SemHandleInput(int sem_id, char *buffer);
static void          InitLut       (void);

static sem_oper_func sem_oper_lut[LUT_SIZE] = {0};

int main(int argc, const char **argv)
{
    SysVSemManipulation(argv);
    (void)argc;
    return 0;
}




int SysVSemManipulation(const char **cmd)
{
    const char welcome_string[] = "Enter semaphore name followed by a command and an option\n";
    int proj_id = 0;
    int sem_id = 0;
    union semun arg;
    int status = SUCCESS;
    char buffer[MAX_INPUT] = {0};

    key_t key = ftok(cmd[1], proj_id);
    if (FAILURE == key)
    {
        printf("FAILED in ftok errno = %d\n", errno);
        return FAILURE;
    }

    errno = 0;
    sem_id = semget(key, 1, 0666 | IPC_CREAT);

    if (FAILURE == sem_id)
    {
        printf("FAILED in semget errno = %d\n", errno);
        return FAILURE;
    }

    if(NULL != cmd[2])
    {    
        errno = 0;
        arg.val = atoi(cmd[2]);
        if (FAILURE == semctl(sem_id, 0, SETVAL, arg))
        {
            printf("FAILED in ctl errno = %d\n", errno);
            return FAILURE;
        }
    }

    InitLut();

    while (FAILURE != status && OK_EXIT != status)
    {
        printf("%s", welcome_string);

        fgets(buffer, MAX_INPUT, stdin);

        status = SemHandleInput(sem_id, buffer);
        if(INVALID_INPUT == status)
        {
            printf("Input was invalid, try again,\n");
        }
    }

    printf("Program exit with status %d\n" ,status);
    return status;
}

static sem_status_t SemHandleInput(int sem_id, char *buffer)
{
    char *input_arg = strtok(buffer, SPACE);
    char args_arr[3] = {0};
    size_t arg_count = 0;
    int status = SUCCESS;

    while (NULL != input_arg)
    {
        switch (arg_count)
        {
        case 0:
            args_arr[COMMAND] = *input_arg;
            status = SUCCESS;
            break;
        case 1:
            args_arr[NUM] = atoi(input_arg);
            status = SUCCESS;
            break;
        case 2:
            args_arr[OPTION] = *input_arg;
            status = (args_arr[OPTION] == 'U' && 2 == strlen(args_arr)) ? SUCCESS : INVALID_INPUT;
            break;

        default:
            status = INVALID_INPUT;
            break;
        }

        ++arg_count;
        input_arg = strtok(NULL, SPACE);
    }

    if(INVALID_INPUT == status)
    {
        return INVALID_INPUT;
    }

    return sem_oper_lut[(int)args_arr[COMMAND]](sem_id, args_arr);
}

static void InitLut()
{
    size_t index = 0;

    for (index = 0; index < LUT_SIZE; ++index)
    {
        sem_oper_lut[index] = &SemInvalid;
    }

    sem_oper_lut['D'] = &SemDecrement;
    sem_oper_lut['I'] = &SemIncrement;
    sem_oper_lut['V'] = &SemGetVal;
    sem_oper_lut['X'] = &SemExit;
    sem_oper_lut['R'] = &SemRemove;
}

static sem_status_t SemInvalid(int sem_id, char *args_arr)
{
    (void)sem_id;
    (void)args_arr;
    return INVALID_INPUT;
}

static sem_status_t SemExit(int sem_id, char *args_arr)
{
    (void)sem_id;
    (void)args_arr;
    return OK_EXIT;
}

static sem_status_t SemDecrement(int sem_id, char *args_arr)
{
    struct sembuf sem_opr = {0};

    if('U' == args_arr[OPTION])
    {
        sem_opr.sem_flg |= SEM_UNDO;
    }

    sem_opr.sem_num = 0;
    sem_opr.sem_op = (-1) * args_arr[NUM];

    return semop(sem_id, &sem_opr, 1);
    
}

static sem_status_t SemIncrement (int sem_id, char *args_arr)
{
    struct sembuf sem_opr = {0};

    if(UNDO_FLAG == args_arr[OPTION])
    {
        sem_opr.sem_flg |= SEM_UNDO;
    }

    sem_opr.sem_num = 0;
    sem_opr.sem_op = args_arr[NUM];

    return semop(sem_id, &sem_opr, 1);
    
}

static sem_status_t SemGetVal(int sem_id, char *args_arr)
{
    union semun arg = {0};
    printf("Semaphore value is: %d\n", semctl(sem_id, 0, GETVAL, arg));
    
    (void)args_arr;

    return SUCCESS;
}

static sem_status_t SemRemove(int sem_id, char *args_arr)
{
    union semun arg;
    (void)args_arr;

    if(FAILURE == semctl(sem_id, 0, IPC_RMID, arg))
    {
        return FAILURE;
    }

    printf("Semaphore removed\n");
    return OK_EXIT;
}
