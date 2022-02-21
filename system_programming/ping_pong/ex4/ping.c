/***********************************
 * ex2. Ping Pong - Source File    *
 * Developer: Tanya                *
 *          Feb 21, 2022           *
 *                                 *
 * Reviewer:  Ofer                 *
************************************/
#define _POSIX_C_SOURCE (199309L)
#define _POSIX_SOURCE
#define _XOPEN_SOURCE (700)
#include <signal.h> /* sigaction, kill */
#include <sys/types.h> /* child_pid_t */
#include <stdio.h>     /* perror */
#include <unistd.h>   /*fork() */
#include <stdlib.h>   /* exit()*/
#include <errno.h>    /* errno */
#include <string.h>  /* strlen */
#include <assert.h> /* assert */
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0) /*error handling macro */

#define TRUE (1)
#define SIGACTION_FAILURE (-1)

pid_t zohara_g = 0; 


static void ChildHandlerFunc(int signal);



int main(int argc, const char *argv[])
{
    struct sigaction sa = {0};
    sa.sa_handler = &ChildHandlerFunc;
    sa.sa_flags |= SA_SIGINFO;
    
    assert (argc == 2);

    if (SIGACTION_FAILURE == sigaction(SIGUSR1, &sa, NULL) && errno != EINTR)
    {
        errExit("Failed to set SIGUSR1 handler");
    }

    zohara_g = atoi(argv[1]);
    kill(zohara_g, SIGUSR2);

    while (TRUE)
    {
        write(STDOUT_FILENO, "PING ", strlen("PING  "));
        pause(); 
    }
    
    return 0;
}

static void ChildHandlerFunc(int signal)
{
    (void)signal; 
    kill(zohara_g, SIGUSR2);
}