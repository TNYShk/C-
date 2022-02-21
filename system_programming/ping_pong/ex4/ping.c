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

pid_t tanya_g = 0; 

static void ChildHandlerFunc(int signal)
{
    (void)signal; 
    write(STDOUT_FILENO, "PING\n", 5);
    kill(tanya_g, SIGUSR2);
}

int main(int argc, const char *argv[])
{
    struct sigaction sa = {0};
    sa.sa_handler = &ChildHandlerFunc;
    sa.sa_flags |= SA_SIGINFO;
    
    if (SIGACTION_FAILURE == sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR1 handler");
    }

    tanya_g = atoi(argv[1]);
    
    kill(tanya_g, SIGUSR2);

    while (TRUE)
    {
        write(STDOUT_FILENO, "PING\n", 5);
        pause(); 
    }
    
    return 0;
}

