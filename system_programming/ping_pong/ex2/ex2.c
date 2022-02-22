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
#include <sys/wait.h> /* wait */
#include <errno.h>    /* errno */
#include <string.h>  /* strlen */

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define FORK_FAILURE (-1)
#define SIGACTION_FAILURE (-1)
#define TRUE (1)

static pid_t child = 0;

static void SignalHandler(int signum);
void PingPong1(void);


void PingPong1(void)
{
    struct sigaction sa = {0};
	sa.sa_handler = SignalHandler;

	child = fork();
	if (0 > child)
    {
        errExit("Failed to fork()");
    }

    if (SIGACTION_FAILURE == sigaction(SIGUSR2, &sa, NULL) )
    {
        errExit("Failed to set SIGUSR2 handler");
    }

    if (0 == child) 
    {
        if (FORK_FAILURE == execlp("./extra","./extra",NULL))
        {
        	errExit("Failed execlp");
        }
    }
    else 
    {
        while(TRUE)
        {
            write(STDOUT_FILENO, "Pong!\n", strlen("Pong! "));
            pause();
        }
    }	
}

static void SignalHandler(int signum)
{	
	if (SIGUSR2 == signum)
	{
		kill(child, SIGUSR1);
	}
}

int main(void)
{
    
    PingPong1();

    return 0;
}
