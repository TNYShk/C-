/***********************************
 * Ping Pong - Source File         *
 * Developer: Tanya                *
 *          Feb 20, 2022           *
 *                                 *
 * Reviewer:                       *
************************************/

#define _POSIX_SOURCE
#define _XOPEN_SOURCE (700)
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

#include <errno.h> /* errno*/
#include <signal.h> /*sigaction */
#include <stdlib.h> /* exit()*/
#include <stdio.h> /* perror */
#include <time.h> /* nanosleep*/
#include <unistd.h> /*fork() */
#include <sys/types.h> /* pid_t */
#include <sys/time.h> /*sig_atomic_t */


#define MAX_PINGS (10)
#define FAIL (-1)


static sig_atomic_t sig_num;


static void SignalHandler(int sig)
{
    sig_num = sig;
}

static void ChildSigHandler(void)
{
   struct timespec sleep;
    sleep.tv_sec = 1;
    sleep.tv_nsec = 0;
    
    while(1)
    {
        pause();
        write(STDOUT_FILENO, "Pong!\n", 6);
        nanosleep(&sleep, 0);
        kill(getppid(), SIGUSR2);
    }
}

static void ParentSigHandler(pid_t pid)
{
    int pings = 0;
    struct timespec sleep;
    sleep.tv_sec = 1;
    sleep.tv_nsec = 0;

    for (; pings < MAX_PINGS; ++pings)
    {
        write(STDOUT_FILENO, "Ping ", 6);
        nanosleep(&sleep, 0);
        kill(pid, SIGUSR1);
        pause();
    }
  kill(pid, SIGTERM);   
}

int main(void)
{
    struct sigaction sa = {0};
    pid_t pid = 0;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SignalHandler;

    if (sigaction(SIGUSR1, &sa, NULL) == FAIL && errno != EINTR)
    {
        errExit("Failed to set SIGUSR1 handler");
    }

    if (sigaction(SIGUSR2, &sa, NULL) == FAIL && errno != EINTR)
    {
        errExit("Failed to set SIGUSR2 handler");
    }

    pid = fork();

    if (pid < 0)
    {
        errExit("Failed to fork()");
    }

    else if (pid == 0)
        
        ChildSigHandler();
    else
        ParentSigHandler(pid);

    return 0;
}