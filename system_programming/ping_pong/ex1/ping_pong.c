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
#include <string.h> /* strlen */

#define MAX_PINGS (10)
#define FAIL (-1)
#define TRUE (1)

static sig_atomic_t sig_num;


static void SignalHandler(int sig)
{
    sig_num = sig;
}

static void ChildSigHandler(void)
{
   
    while(TRUE)
    {
        pause();
        write(STDOUT_FILENO, "Lalala!\n", strlen("Lalala! "));
        sleep(1);
        kill(getppid(), SIGUSR2);
    }
}

static void ParentSigHandler(pid_t pid)
{
    int pings = 0;
   
    for (; pings < MAX_PINGS; ++pings)
    {
        write(STDOUT_FILENO, "Lilili ", strlen("Lilili  "));
        sleep(0);
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
    sa.sa_handler = &SignalHandler;

    if (FAIL == sigaction(SIGUSR1, &sa, NULL) || FAIL == sigaction(SIGUSR2, &sa, NULL))
    {
        errExit("Failed to set SIGUSR1 or 2 handler");
    }

    pid = fork();

    if (0 > pid)
    {
        errExit("Failed to fork()");
    }

    else if (0 == pid)
        
        ChildSigHandler();
    else
        ParentSigHandler(pid);

    return 0;
}