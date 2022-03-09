/********************************************
 * WATCHDOG - Source Code                   *
 * Developer: Tanya                   		*
 * Mar 8, 2022                   	     	*
 *                                          *
 *      Reviewed by        	 	  	 		*
*********************************************/
#define _XOPEN_SOURCE (700)
#define _POSIX_C_SOURCE 200112L 
#include <time.h>        /* time_t      */
#include <assert.h>      /* assert      */
#include <pthread.h>     /* thread_t    */
#include <signal.h>      /* sigaction   */
#include <sys/types.h>   /* pid_t       */
#include <unistd.h>      /* fork        */
#include <stdio.h>       /* printf      */
#include <stdlib.h>      /* atoi        */
#include <errno.h>       /* errno       */
#include <string.h>      /* strlen      */
#include "scheduler.h"		  /* scheduler API        */
#include "semaphore_sys_v.h"  /* sys_v sempahore API  */
#include "watchdog.h"         /* watchdog API         */

#ifdef DEBUG
	#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#else
	#define errExit(msg) do { perror(msg); return(errno); } while (0)
#endif

#define atomic_sync_or_and_fetch(destptr, flag) __sync_or_and_fetch(destptr, flag)
#define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval)


	
#define PING_EVERY (1)
#define CHECK_ALIVE_EVERY (5)
#define SUCCESS (0)
#define FAIL (-1)
#define ARGZ (256)
#define PATHNAME ("/kickdog")

static void *WrapperSchedSem(void *something);
static void SomeFailDie(scheduler_t *sched);
static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext);
static void SigHandlerKill(int sig);
static int TaskPingAlive(void *args);
static int TaskCheckAlive(void *args);
static int TaskStopSched(void *pid);
static int InitSched(void);
static int InitProcess(char *argv[], int semid);
static int Revive(void);

typedef struct revive
{
	char buffer[ARGZ];
	char *whole;
	pid_t pid_child;
}revive_t;

scheduler_t *new_sched;
static int alive_g = 0;
static int semid;
static int sched_flag = 0;
pthread_t watchdog_t_g = {0};
revive_t revive_g;



int WDStart(int argc, char *argv[])
{
	
	struct sigaction sa = {0};
	struct sigaction ka = {0};
	(void)argc;

	sa.sa_sigaction = &SigHandlerAlive;
	ka.sa_handler = &SigHandlerKill;
    sa.sa_flags |= SA_SIGINFO;
	
    if (SUCCESS != sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR1 handler");
    }

    if (SUCCESS != sigaction(SIGUSR2, &ka, NULL))
    {
        errExit("Failed to set SIGUSR2 handler");
    }

    semid = InitSem(0);
    if(0 > semid)
    {
    	errExit("Init_sem");
    }
	
	assert(SUCCESS == InitSched());

	if(SUCCESS != pthread_create(&watchdog_t_g, NULL, &WrapperSchedSem, new_sched))
	{
		SomeFailDie(new_sched);
		write(STDOUT_FILENO, "pthread create watchdog SIGUSR2\n", 25);
		kill(revive_g.pid_child, SIGUSR2);
		errExit("pthread_create");
	}
	
    if(NULL == getenv("REVDOG"))
	{
		InitProcess(argv, semid);
		SemDecrement(semid,1);
	}
	else 
	{
		if(SUCCESS != unsetenv("REVDOG"))
		{
			errExit("unsetenv fail");
		}
	}

	return SUCCESS;
}

void WDStop(void)
{
	
	write(STDOUT_FILENO, "WDStop\n", strlen("WDStop "));
	kill(revive_g.pid_child, SIGUSR2);
	
	pthread_join(watchdog_t_g, NULL);
	SomeFailDie(new_sched);
}



static int InitProcess(char *argv[], int semid)
{
	char semchar[ARGZ] = {0};
	char cwd[ARGZ] = {0};
	
	getcwd(cwd, ARGZ);
	
	sprintf(semchar,"%d", semid);

	revive_g.pid_child = fork();
		
	if(0 > revive_g.pid_child)
	{
		errExit("fork fail");
	}
	if (0 == revive_g.pid_child) /* in watchdog process */
	{
		strcat(cwd, PATHNAME);
		
		if(FAIL == execl(cwd,cwd,semchar, NULL))
		{
			errExit("Failed execv");
		}
	}

    memcpy(revive_g.buffer, argv[0], strlen(argv[0]));
    revive_g.whole = revive_g.buffer + strlen(revive_g.buffer) + 1;
 	strcat(revive_g.whole, semchar);

	return SUCCESS;
}

static int InitSched(void)
{
	new_sched = SchedCreate();
	if(NULL == new_sched)
	{
		errExit("SchedCreate failed");
	}

	if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskPingAlive, NULL, 
    							NULL, NULL, time(0) + PING_EVERY)))
    {
    	SomeFailDie(new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    	
    }
    if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskCheckAlive, NULL, 
    					NULL, NULL, time(0) + CHECK_ALIVE_EVERY)))
    {
    	SomeFailDie(new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    }

    if(UIDIsSame(UIDBadUID,SchedAddTask(new_sched, &TaskStopSched, NULL, 
    					NULL, NULL, time(0) + CHECK_ALIVE_EVERY)))
    {
    	SomeFailDie(new_sched);
    	errExit("UIDBadUID == SchedAddTask");
    }

	printf("in WATCHDOG ppid is %d, and pid is %d\n", getppid(), getpid()); 
	return SUCCESS;
}




static void SomeFailDie(scheduler_t *sched)
{
    SchedDestroy(sched);
    sched = NULL;
   	SemRemove(semid); 
}

static void *WrapperSchedSem(void *something)
{
	printf("schedrun? %d\n",SchedRun((scheduler_t *)something));
	return NULL;
}


static int TaskPingAlive(void *args)
{
	(void)args;

	if(0 != revive_g.pid_child)
	{
		kill(revive_g.pid_child, SIGUSR1);
	}

	return PING_EVERY;
}

static int TaskCheckAlive(void *args)
{
	(void)args;
	if(!__sync_bool_compare_and_swap(&alive_g, 1, 0))
	{
		write(STDOUT_FILENO, "REVIVE PLEASE\n", strlen("REVIVE PLEASE "));
		Revive();
	}
	
	return CHECK_ALIVE_EVERY;
}

static int Revive(void)
{
	char revive[ARGZ] = {0};

	getcwd(revive, ARGZ);
	strcat(revive, PATHNAME);

	revive_g.pid_child = fork();
	if(0 == revive_g.pid_child)
	{
		if(FAIL == execl(revive,revive, revive_g.whole, NULL))
    	{
        	errExit("Failed execl");
    	}
	}
	return SUCCESS;
}


static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;	
	write(STDOUT_FILENO, "Hungry Barking DOG\n", strlen("Hungry Barking DOG  "));
	atomic_sync_or_and_fetch(&alive_g, 1);
	revive_g.pid_child = info->si_pid;
}

static void SigHandlerKill(int sig)
{
	(void)sig;
	if (NULL != new_sched)
	{
		atomic_compare_and_swap(&sched_flag,0 , 1);
	}

}

int TaskStopSched(void *pid)
{
	(void)pid;
	if (1 == sched_flag)
	{
		SchedStop(new_sched);
	}
	return PING_EVERY;
}

