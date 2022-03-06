#include <sys/types.h>  /* key_t           */
#include <sys/ipc.h>    /* ftok            */
#include <sys/sem.h>    /* sys V semaphore */
#include <stdio.h>      /* printf          */
#include <stdlib.h>     /* atoi            */
#include <string.h>     /* strtok          */
#include <errno.h>      /* errno           */
#include <limits.h>     /* CHAR_MAX        */
#include <unistd.h> /* errors */
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define MEXLEN (4096)
#define SPACE     (" ")
#define UNDO_FLAG ('U')

typedef enum bool
{
    FALSE = 0,
    TRUE = 1
} bool_t;

typedef enum status
{
    FAILURE = -1,
    SUCCESS = 0,
    INVALID_INPUT,
    VALID_EXIT
} sem_status_t;

enum arg_arr_vals
{
    COMMAND,
    NUM,
    OPTION,
    NUM_ARG_VALS
};

union semun 
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
#if defined(__linux__)
    struct seminfo *__buf;
#endif
};

int SysVSemManipulation(const char **cmd);

/* LUT functions */
typedef sem_status_t (*sem_oper_func)(int sem_id, char *args_arr);

static sem_status_t  SemWait       (int sem_id, char *args_arr);
static sem_status_t  SemPost       (int sem_id, char *args_arr);
static sem_status_t  SemGetValue   (int sem_id, char *args_arr);
static sem_status_t  SemRemove     (int sem_id, char *args_arr);
static sem_status_t  SemInvalid    (int sem_id, char *args_arr);
static sem_status_t  SemExit       (int sem_id, char *args_arr);
static sem_status_t  SemHandleInput(int sem_id, char *buffer);
static void          InitLut       (void);

static sem_oper_func sem_oper_lut[CHAR_MAX] = {0};


int main(int argc, const char *argv[])
{
    if (2 != argc)
    {
        printf("not enpugh args! need: ./a.out <sem_name>");
        return FAILURE;
    }

    SysVSemManipulation(argv);

    return SUCCESS;
}

int SysVSemManipulation(const char **cmd)
{
    key_t key = 0;
    int sem_id = 0;
    int proj_id = 0;
    union semun arg = {0};
    int status = SUCCESS;
    char buffer[MEXLEN] = {0};

    if (FAILURE == (key = ftok(cmd[1], proj_id)))
    {
        errExit("ftok");
    }


    if (FAILURE == (sem_id = semget(key, 1, 0666 | IPC_CREAT)))
    {
        errExit("semget");
    }

    if (NULL != cmd[2])
    {    
       
        arg.val = atoi(cmd[2]);
        if (FAILURE == semctl(sem_id, 0, SETVAL, arg))
        {
            errExit("semctl");
        }
    }

    InitLut();

    while (FAILURE != status && VALID_EXIT != status)
    {
        printf("%s\n%s\n",
            "Enter command: [D]ecrement, [I]ncrement, [V]iew, [R]emove, e[X]it.",
            "If decrementing/incrementing, enter amount as well");

        if (INVALID_INPUT == (status = 
            SemHandleInput(sem_id, fgets(buffer, MEXLEN, stdin))))
        {
            printf("Invalid input.\n");
        }
    }

    printf("Program exit with status %d\n", status);
    return status;
}

static sem_status_t SemHandleInput(int sem_id, char *buffer)
{
    char *input_arg = strtok(buffer, SPACE);
    char args_arr[NUM_ARG_VALS] = {0};
    size_t arg_count = 0;
    int status = SUCCESS;

    do
    {
        switch (arg_count++)
        {
        case COMMAND:
            args_arr[COMMAND] = *input_arg;
            status = SUCCESS;
            break;
        case NUM:
            args_arr[NUM] = atoi(input_arg);
            status = SUCCESS;
            break;
        case OPTION:
            args_arr[OPTION] = *input_arg;
            status = (args_arr[OPTION] == 'U' && 2 == strlen(args_arr)) ? SUCCESS : INVALID_INPUT;
            break;

        default:
            status = INVALID_INPUT;
            break;
        }

    } while (NULL != (input_arg = strtok(NULL, SPACE)));

    if(INVALID_INPUT == status)
    {
        return INVALID_INPUT;
    }

    return sem_oper_lut[(int)args_arr[COMMAND]](sem_id, args_arr);
}

static void InitLut()
{
    size_t index = 0;
    for (index = 0; index < CHAR_MAX; ++index)
    {
        sem_oper_lut[index] = SemInvalid;
    }

    sem_oper_lut['D'] = SemWait;
    sem_oper_lut['I'] = SemPost;
    sem_oper_lut['V'] = SemGetValue;
    sem_oper_lut['X'] = SemExit;
    sem_oper_lut['R'] = SemRemove;
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

    return VALID_EXIT;
}

static sem_status_t SemWait(int sem_id, char *args_arr)
{
    struct sembuf sem_opr = {0};

    sem_opr.sem_num = 0;
    sem_opr.sem_op = -args_arr[NUM];
    sem_opr.sem_flg |= SEM_UNDO * (UNDO_FLAG == args_arr[OPTION]);

    return semop(sem_id, &sem_opr, 1);
}

static sem_status_t SemPost(int sem_id, char *args_arr)
{
    struct sembuf sem_opr = {0};

    sem_opr.sem_num = 0;
    sem_opr.sem_op = args_arr[NUM];
    sem_opr.sem_flg |= SEM_UNDO * (UNDO_FLAG == args_arr[OPTION]);

    return semop(sem_id, &sem_opr, 1);
}

static sem_status_t SemGetValue(int sem_id, char *args_arr)
{
    union semun arg = {0};
    (void)args_arr;

    printf("Semaphore value is: %d\n", semctl(sem_id, 0, GETVAL, arg));
    
    return SUCCESS;
}

static sem_status_t SemRemove(int sem_id, char *args_arr)
{
    union semun arg = {0};
    (void)args_arr;

    if (FAILURE == semctl(sem_id, 0, IPC_RMID, arg))
    {
         errExit("semctl");
    }

    printf("Semaphore removed\n");
    return VALID_EXIT;
}
