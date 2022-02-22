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

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define SIGACTION_FAILURE (-1)
#define TRUE (1)

static void SignalHandler(int signum);
void PingPong(void);


void PingPong(void)
{
    struct sigaction sa = {0};
	sa.sa_handler = &SignalHandler;
  
    if (SIGACTION_FAILURE == sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR1 handler");
    }
 
    kill(getppid(), SIGUSR2);

    while (TRUE)
    {
        write(STDOUT_FILENO, "Ping ", strlen("Ping  "));
        pause();
    }
	
}

static void SignalHandler(int signum)
{	
	if (SIGUSR1 == signum)
	{
		kill(getppid(), SIGUSR2);
	}

}

int main(void)
{
    PingPong();

    return 0;
}
