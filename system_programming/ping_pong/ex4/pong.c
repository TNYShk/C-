#define _POSIX_C_SOURCE 199309L
#define _POSIX_SOURCE
#define _XOPEN_SOURCE (700)
#include <signal.h> /* signal, kill */
#include <sys/types.h> /* child_pid_t */
#include <stdio.h>     /* perror */
#include <unistd.h>   /*fork() */
#include <stdlib.h>   /* exit()*/
#include <errno.h>    /* errno */
#include <string.h>  /* strlen */

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define TRUE (1)
#define SIGACTION_FAILURE (-1)

static void ChildHandlerFunc(int signal, siginfo_t *info, void *ucontext)
{
    (void)signal;
    (void)ucontext; 
    write(STDOUT_FILENO, "PONG\n", 5);
    kill(info->si_pid, SIGUSR1);
}

int main()
{
    struct sigaction sa = {0};
    sa.sa_sigaction = &ChildHandlerFunc;

    if (SIGACTION_FAILURE == sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR1 handler");
    }
  

    while (TRUE)
    {
        write(STDOUT_FILENO, "PONG\n", 5);
        pause(); 
    }
    
    return 0;
}

