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

#include "semaphore_posix.h"
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)


#define MAXLEN (251)





int main(int argc, char *argv[])
{
   


    static char name[MAXLEN] = {0};
    unsigned int value = 2;
    sem_t *semP = NULL;
    int tt = 0;
    int tet = 0;
    assert(3 == argc);
    *name = *argv[1];

    semP = sem_open(name, O_CREAT, 0666, atoi(argv[2]));
   
    printf("created named semaphore? %s, value: %d\n", name, value);
    tt = sem_trywait(semP);
    sem_post(semP);
    tt = sem_getvalue(semP, &tet);
    printf("trying sem_getval : %d\n", tet);
    sem_close(semP);
    sem_unlink(name);

    return 0;
}

int PosixSemManipulation(const char **cmd)
{
    return -1;
}