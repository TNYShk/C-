/***********************************
 * Ping Pong - Source File         *
 * Developer: Tanya                *
 *          Feb 20, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/
#define _POSIX_C_SOURCE 1
#define _POSIX_SOURCE
#define _XOPEN_SOURCE (700)
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#include <sys/types.h>  /* pid_t */
#include <stdio.h>     /* perror */
#include <unistd.h>   /*fork() */
#include <stdlib.h>   /* exit()*/
#include <signal.h>   /*sigaction */
#include <sys/wait.h> /* wait */
#include <errno.h>    /* errno */

#define MAX_PINGS (10)
#define FAIL (-1)

sigset_t saveMask, blockMask;


void ChildSigHandler(void);
void ParentSigHandler(pid_t pid);
void SigHandle(int signum);


void SigHandle(int signum)
{
	(void)signum;
}

void ParentSigHandler(pid_t pid)
{
	int y = 0;

    for (y = 0; y < MAX_PINGS; ++y)
    {
        sleep(1);
        write(STDOUT_FILENO, "Ping ", 6);
        kill(pid, SIGUSR1);

        if (sigsuspend(&saveMask) == FAIL && errno != EINTR)
            errExit("sigsuspend");
    }

    return;
}

void ChildSigHandler(void)
{
	int x = 0;

    for(x = 0; x < MAX_PINGS; ++x)
    {
        if (sigsuspend(&saveMask) == FAIL && errno != EINTR)
        {
            errExit("sigsuspend");
        }
      
        write(STDOUT_FILENO, "Pong!\n", 6);
        kill(getppid(), SIGUSR1);
        sleep(2);
    }

    return;
}


int main(void)
{
    struct sigaction sa = {0};
    pid_t pid = 0;

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGUSR1);

    if (sigprocmask(SIG_BLOCK, &blockMask, &saveMask) == FAIL)
        errExit("sigprocmask");

   
   
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SigHandle;

    if (sigaction(SIGUSR1, &sa, NULL) == FAIL)
        errExit("sigaction");

    pid = fork();

    if (pid == 0)
        ChildSigHandler();
    else
        ParentSigHandler(pid);

    return 0;
}


