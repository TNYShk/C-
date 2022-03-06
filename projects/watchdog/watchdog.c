#define _XOPEN_SOURCE (700)

#include <assert.h>      /* assert    */
#include <pthread.h>     /* thread_t  */
#include <signal.h>      /* sigaction */
#include <sys/types.h>   /* pid_t     */
#include <unistd.h>      /* fork      */
#include <stdio.h>       /* printf    */
#include <fcntl.h>  /* O_* const.*/
#include <sys/stat.h> /* mode const. */
#include <semaphore.h> /*semaphore */
#include <stdlib.h> /* atoi */
#include <errno.h> /* errno */
#include <string.h> /*strcmp */
#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define atomic_sync_fetch_or(destptr, flag) __sync_fetch_and_or(destptr, flag)
#define atomic_sync_or_and_fetch(destptr, flag) __sync_or_and_fetch(destptr, flag)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)

#include "scheduler.h"
#include "semaphore_posix.h"
#include "watchdog.h"

#define PING_EVERY (1)
#define CHECK_ALIVE_EVERY (5)

static int alive_g = 0;
static int sem_id;
pid_t pid_child;




int WDStart(int argc, char *argv[])
{
	
	scheduler_t *new_sched = NULL;
	struct sigaction sa = {0};
	struct sigaction ka = {0};

	

	ka.sa_sigaction = &SigHandlerKill;
	sa.sa_sigaction = &SigHandlerAlive;
    sa.sa_flags |= SA_SIGINFO;
    ka.sa_flags |= SA_SIGINFO;

  
    if (SUCCESS != sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR2 handler");
    }

    if (SUCCESS != sigaction(SIGUSR2, &ka, NULL))
    {
        errExit("Failed to set SIGUSR2 handler");
    }

    semid = InitSem(1);
    if(0 > semid)
    {
    	errExit("Init_sem");
    }

    new_sched = SchedCreate();
    assert(NULL != new_sched);

    if(UIDBadUID == SchedAddTask(new_sched, &PingAlive, NULL, NULL, NULL, time(0) + PING_EVERY))
    {
    	SchedDestroy(new_sched);
    	new_sched = NULL;
    	SemRemove(semid);
    	errExit("UIDBadUID == SchedAddTask");
    	
    }
    if(UIDBadUID == SchedAddTask(new_sched, &CheckAlive, NULL, NULL, NULL, time(0) + CHECK_ALIVE_EVERY))
    {
    	SchedDestroy(new_sched);
    	new_sched = NULL;
    	SemRemove(semid);
    	errExit("UIDBadUID == SchedAddTask");
    }
		
   
    pid_child = fork();

	return 0;
}



static void *WatchdogThread(void *something)
{
    create semaphore
}

int PingAlive(void *args)
{
	(void)args;

	if(pid_child != 0)
	{
		kill(pid_child, SIGUSR1);
	}

	return PING_EVERY;
}

int PingAlive2(void *args)
{
	(void)args;
	
	if(pid_child == 0)
	{
		kill(getppid(), SIGUSR2);
	}

	return 1;
}




int CheckAlive(void *args)
{
	if(atomic_compare_and_swap(&alive_g, 1, 0))
	{
		return CHECK_ALIVE_EVERY;
	
	}
	else
	{
			/* REVIVE*/
	}
	
}

static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext)
{
	atomic_sync_or_and_fetch(&alive_g, 1);
	pid_child = info->si_pid;
	(void)sig;
	(void)ucontext;
	
}

static void SigHandlerKill(int sig, siginfo_t *info, void *ucontext)
{
	free scheduler;
	pthread_join
	SemRemove(sem_id);
	
	atomic_compare_and_swap(&alive_g, 1, 0)
}