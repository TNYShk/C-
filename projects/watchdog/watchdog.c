#define _XOPEN_SOURCE (700)
#define _POSIX_C_SOURCE 199309L
#include <time.h> /*time_t */
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
#include "semaphore_sys_v.h"
#include "watchdog.h"
#include "uid.h"

#define PING_EVERY (1)
#define CHECK_ALIVE_EVERY (5)
#define SUCCESS (0)
#define FAIL (-1)

static void *WrapperSchedSem(void *something);
static void SomeFailDie(scheduler_t *sched);
static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext);
static void SigHandlerKill(int sig, siginfo_t *info, void *ucontext);
int TaskPingAlive(void *args);
int TaskCheckAlive(void *args);
int PingAlive2(void *args);


typedef struct revive
{
	char **cmds;
	scheduler_t *new_sched;
	pid_t pid_child;
}revive_t;


static int alive_g = 0;
static int semid;

pthread_t watchdog_t_g = {0};
revive_t new_g;






int WDStart(int argc, char *argv[])
{
	
	
	struct sigaction sa = {0};
	struct sigaction ka = {0};
	

	ka.sa_sigaction = &SigHandlerKill;
	sa.sa_sigaction = &SigHandlerAlive;
    sa.sa_flags |= SA_SIGINFO;
    ka.sa_flags |= SA_SIGINFO;

    new_g.cmds[1] = argv[1];
  
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

    new_g.new_sched = SchedCreate();
    if(NULL == new_g.new_sched)
    {
    	SemRemove(semid);
    }

    if(UIDIsSame(UIDBadUID,SchedAddTask(new_g.new_sched, &TaskPingAlive, NULL, 
    							NULL, NULL, time(0) + PING_EVERY)))
    {
    	SomeFailDie(new_g.new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    	
    }
    if(UIDIsSame(UIDBadUID,SchedAddTask(new_g.new_sched, &TaskCheckAlive, NULL, 
    					NULL, NULL, time(0) + CHECK_ALIVE_EVERY)))
    {
    	SomeFailDie(new_g.new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    }
		
    new_g.pid_child = fork();
    if(0 > new_g.pid_child)
    {
    	errExit("fork fail");
    }
    if (0 == new_g.pid_child) /* in watchdog process */
    {
    	SchedRun(new_g.new_sched);
    	SchedDestroy(new_g.new_sched);
    }
    else /* in ward process */
    {
    	if(SUCCESS != pthread_create(&watchdog_t_g, NULL, &WrapperSchedSem, new_g.new_sched))
    	{
    		SomeFailDie(new_g.new_sched);
    		kill(new_g.pid_child, SIGUSR2);
    		errExit("pthread_create");
    	}
    }
    

	return 0;
}

void WDStop(void)
{
	kill(new_g.pid_child, SIGUSR2);
	pthread_join(watchdog_t_g, NULL);
}


static void SomeFailDie(scheduler_t *sched)
{
    SchedDestroy(sched);
    sched = NULL;
    SemRemove(semid);
}

static void *WrapperSchedSem(void *something)
{
	SchedRun((scheduler_t *)something);
	return NULL;
}




int TaskPingAlive(void *args)
{
	(void)args;

	if(0 != new_g.pid_child)
	{
		kill(new_g.pid_child, SIGUSR1);
	}

	return PING_EVERY;
}

int TaskCheckAlive(void *args)
{
	(void)args;
	if(!atomic_compare_and_swap(&alive_g, 1, 0))
	{
		/* REVIVE*/
	
	}
	
	return CHECK_ALIVE_EVERY;
}

int PingAlive2(void *args)
{
	(void)args;
	
	if(0 == new_g.pid_child)
	{
		kill(getppid(), SIGUSR2);
	}

	return PING_EVERY;
}






static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext)
{
	atomic_sync_or_and_fetch(&alive_g, 1);
	new_g.pid_child = info->si_pid;
	(void)sig;
	(void)ucontext;	
}

static void SigHandlerKill(int sig, siginfo_t *info, void *ucontext)
{
	SchedStop(new_g.new_sched);
	pthread_join(new_g.pid_child, NULL);
	SemRemove(semid);
	
	atomic_compare_and_swap(&alive_g, 1, 0);
	kill(new_g.pid_child, SIGUSR2);
	
}

