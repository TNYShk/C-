/***********************************
 * ex4. Ping Pong - Source File    *
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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define TRUE (1)
#define SIGACTION_FAILURE (-1)

static void ChildHandlerFunc(int signal, siginfo_t *info, void *ucontext);

int main()
{
    struct sigaction sa = {0};
    sa.sa_sigaction = &ChildHandlerFunc;
    sa.sa_flags |= SA_SIGINFO;

    if (SIGACTION_FAILURE == sigaction(SIGUSR2, &sa, NULL) && errno != EINTR)
    {
        errExit("Failed to set SIGUSR2 handler");
    }
  
    while (TRUE)
    {
        write(STDOUT_FILENO, "PONG\n", strlen("PONG! "));
        pause(); 
    }
    
    return 0;
}

static void ChildHandlerFunc(int signal, siginfo_t *info, void *ucontext)
{
    (void)signal;
    (void)ucontext; 
    kill(info->si_pid, SIGUSR1);
}