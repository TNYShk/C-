/***********************************
 * ex1. Ping Pong - Source File    *
 * Developer: Tanya                *
 *          Feb 21, 2022           *
 *                                 *
 * Reviewer:  Ofer                 *
************************************/
#define _POSIX_C_SOURCE (199309L)
#define _POSIX_SOURCE
#define _XOPEN_SOURCE (700)
#include <signal.h>    /* sigaction, kill */
#include <sys/types.h> /* pid_t */
#include <stdio.h>     /* perror */
#include <unistd.h>   /*fork() */
#include <stdlib.h>   /* exit() */
#include <sys/wait.h> /* wait */
#include <errno.h>    /* errno */
#include <string.h>  /* strlen */
#include <time.h>   /* time */

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define SECONDS_TO_RUN (2)
#define FAIL_SIGACTION (-1)

static void HandleSigUsr(int signal);
static int is_ready_to_signal = 0;


int main(void)
{
	pid_t target = 0;
	struct sigaction handle_siguser = {0};
	int sig = SIGUSR1; /* default for parent*/
	const char *msg = "Ping \n";
	time_t start = time(NULL);

	handle_siguser.sa_handler = &HandleSigUsr;
	handle_siguser.sa_flags = 0;

 if (FAIL_SIGACTION == sigaction(SIGUSR1, &handle_siguser, NULL))
	errExit("Failed to set SIGUSR1 handler");

 if (FAIL_SIGACTION == sigaction(SIGUSR2, &handle_siguser, NULL))
	errExit("Failed to set SIGUSR2 handler");	
	
	target = fork();

	if(0 == target)
	{
		target = getppid();
		sig = SIGUSR2;
		msg = "Pong!\n";
	}
	else
	{
		is_ready_to_signal = 1;
	}

	while(time(NULL) < start + SECONDS_TO_RUN)
	{
		if (1 == is_ready_to_signal)
		{	
			printf(msg);
			is_ready_to_signal = 0;
			kill(target, sig);
		}
	}

	return 0;
}


static void HandleSigUsr(int signal)
{	
	(void)signal;
	is_ready_to_signal = 1;
}