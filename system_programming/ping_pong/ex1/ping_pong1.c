/***********************************
 * Ping Pong - Source File         *
 * Developer: Tanya                *
 *          Feb 20, 2022           *
 *                                 *
 * Reviewer:  Ofer                 *
************************************/
#define _POSIX_C_SOURCE (199309L)
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

#define MAX_PINGS (20)
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

    for (; y < MAX_PINGS; ++y)
    {
        sleep(0);
        write(STDOUT_FILENO, "Ping ", strlen("Ping "));
        kill(pid, SIGUSR1);

        if (FAIL == sigsuspend(&saveMask) && errno != EINTR)
            errExit("sigsuspend");
    }

    return;
}

void ChildSigHandler(void)
{
	int x = 0;

    for(; x < MAX_PINGS; ++x)
    {
        if (sigsuspend(&saveMask) == FAIL && errno != EINTR)
        {
            errExit("sigsuspend");
        }
      
        write(STDOUT_FILENO, "Pong!\n", strlen("Pong!  "));
        kill(getppid(), SIGUSR1);
        sleep(1);
    }

    return;
}


int main(void)
{
    struct sigaction sa = {0};
    pid_t pid = 0;

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGUSR1);

    if (FAIL == sigprocmask(SIG_BLOCK, &blockMask, &saveMask))
        errExit("sigprocmask");

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SigHandle;

    if (FAIL == sigaction(SIGUSR1, &sa, NULL))
        errExit("sigaction");

    pid = fork();

    if (0 == pid)
        ChildSigHandler();
    else
        ParentSigHandler(pid);

    return 0;
}


