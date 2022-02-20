#define _POSIX_SOURCE
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#include <sys/types.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h> /* wait */
#include <errno.h>



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

    for (y = 0; y < 10; ++y)
    {
        write(STDOUT_FILENO, "Ping ", 6);
        
        kill(pid, SIGUSR1);

        if (sigsuspend(&saveMask) == -1 && errno != EINTR)
            errExit("sigsuspend");
    }

    return;
}

void ChildSigHandler(void)
{
	int x = 0;

    for(x = 0; x < 10; ++x)
    {
        if (sigsuspend(&saveMask) == -1 && errno != EINTR)
        {
            errExit("sigsuspend");
        }

        write(STDOUT_FILENO, "Pong!\n", 6);
   
        kill(getppid(), SIGUSR1);
    }

    return;
}


int main(void)
{
    struct sigaction sa = {0};
    pid_t pid = 0;

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGUSR1);

    if (sigprocmask(SIG_BLOCK, &blockMask, &saveMask) == -1)
        errExit("sigprocmask");

   
   
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SigHandle;

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
        errExit("sigaction");

    pid = fork();

    if (pid == 0)
        ChildSigHandler();
    else
        ParentSigHandler(pid);

    return 0;
}


