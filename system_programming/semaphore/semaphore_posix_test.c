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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)



int main(int argc, const char *argv[])
{

    assert(2 < argc);
    
    PosixSemManipulation(argv);
   
    return 0;
}



