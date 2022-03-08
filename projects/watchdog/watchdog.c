#define _XOPEN_SOURCE (700)
/* #define _POSIX_C_SOURCE 199309L */
#define _POSIX_C_SOURCE 200112L 
#include <time.h>        /* time_t      */
#include <assert.h>      /* assert      */
#include <pthread.h>     /* thread_t    */
#include <signal.h>      /* sigaction   */
#include <sys/types.h>   /* pid_t       */
#include <unistd.h>      /* fork        */
#include <stdio.h>       /* printf      */
#include <fcntl.h>       /* O_* const.  */
#include <sys/stat.h>    /* mode const. S*/
#include <stdlib.h>      /* atoi        */
#include <errno.h>       /* errno       */
#include <string.h>      /* strcmp      */

#define errExit(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define atomic_sync_fetch_or(destptr, flag) __sync_fetch_and_or(destptr, flag)
#define atomic_sync_or_and_fetch(destptr, flag) __sync_or_and_fetch(destptr, flag)
/* #define atomic_compare_and_swap(destptr, oldval, newval) __sync_bool_compare_and_swap(destptr, oldval, newval) */
#define atomic_sync_add_fetch(destptr, incrby) __sync_add_and_fetch(destptr, incrby)
#include "scheduler.h"
#include "semaphore_sys_v.h"
#include "watchdog.h"
#include "uid.h"

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
static void InitSched(void);
static void Revive(char *argv[]);


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
	char semchar[ARGZ] = {0};
	char cwd[ARGZ] = {0};
	getcwd(cwd, ARGZ);
	printf("%s\n",cwd);
	
	
	sa.sa_sigaction = &SigHandlerAlive;
	ka.sa_handler = &SigHandlerKill;
    sa.sa_flags |= SA_SIGINFO;
	
	/* errno = 0;
	printf("set env? %d\n",putenv("TNY=26"));
	printf("errno? %d\n", errno); */

    if (SUCCESS != sigaction(SIGUSR1, &sa, NULL))
    {
        errExit("Failed to set SIGUSR1 handler");
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
	SemDecrement(semid,1);
	printf("post dec, in watchdog:sem val is %d\n", SemGetVal(semid) );

    sprintf(semchar,"%d", semid);
    memcpy(revive_g.buffer, argv[0], strlen(argv[0]));
    revive_g.whole = revive_g.buffer + strlen(revive_g.buffer) + 1;
 	strcat(revive_g.whole, semchar);
	printf("testing revive_g.whole: %s\n",revive_g.whole );
    /*revive_g.whole = strcat(cwd, revive_g.buffer + 1);
    printf("testing: %s\n",revive_g.whole );*/
	
	InitSched();

	
    if(NULL == getenv("REVDOG"))
	{
		revive_g.pid_child = fork();
		/* printf("child_pid in WDStart is: %d\n",revive_g.pid_child); */
		if(0 > revive_g.pid_child)
		{
			errExit("fork fail");
		}
		if (0 == revive_g.pid_child) /* in watchdog process */
		{
			strcat(cwd, PATHNAME);
			/* printf("semchar is: %s\n", semchar);
			printf("strcat cwd is: %s\n", cwd); */

			if(FAIL == execl(cwd,cwd,semchar, NULL))
			{
				errExit("Failed execv");
			}
		}
		/* else  in ward process 
		{
			if(SUCCESS != pthread_create(&watchdog_t_g, NULL, &WrapperSchedSem, new_sched))
			{
				SomeFailDie(new_sched);
				kill(revive_g.pid_child, SIGUSR2);
				errExit("pthread_create");
			}

		} */
	}
	else 
	{
		if(SUCCESS != unsetenv("REVDOG"))
		{
			errExit("unsetenv fail");
		}
	}
	/* in ward process */
	if(SUCCESS != pthread_create(&watchdog_t_g, NULL, &WrapperSchedSem, new_sched))
	{
		SomeFailDie(new_sched);
		write(STDOUT_FILENO, "pthread create watchdog SIGUSR2\n", 25);
		kill(revive_g.pid_child, SIGUSR2);
		errExit("pthread_create");
	}


	return 0;
}

static void InitSched(void)
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
}

void WDStop(void)
{
	SemDecrement(semid,1);
	write(STDOUT_FILENO, "line 192 SIGUSR2\n", strlen("line 187 SIGUSR2 "));
	kill(revive_g.pid_child, SIGUSR2);
	pthread_join(watchdog_t_g, NULL);
	SomeFailDie(new_sched);
}


static void SomeFailDie(scheduler_t *sched)
{
    SchedDestroy(sched);
    sched = NULL;
   /*  SemRemove(semid); */
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
		/* REVIVE*/
		Revive((char **)args);
	}
	
	return CHECK_ALIVE_EVERY;
}

static void Revive(char *argv[])
{
	char revive[ARGZ] = {0};

	getcwd(revive, ARGZ);
	strcat(revive, PATHNAME);

	revive_g.pid_child = fork();
	if(FAIL == execl(revive,revive, revive_g.whole, NULL))
    {
        errExit("Failed execl");
    }

}


static void SigHandlerAlive(int sig, siginfo_t *info, void *ucontext)
{
	(void)sig;
	(void)ucontext;	
	write(STDOUT_FILENO, "Barking hungry DOG\n", strlen("Barking hungry DOG  "));
	atomic_sync_or_and_fetch(&alive_g, 1);
	revive_g.pid_child = info->si_pid;
}

static void SigHandlerKill(int sig)
{
	(void)sig;
	if (NULL != new_sched)
	{
		__sync_bool_compare_and_swap(&sched_flag,0 , 1);
	}

}

int TaskStopSched(void *pid)
{
	if (1 == sched_flag)
	{
		SchedStop(new_sched);
	}
	return PING_EVERY;
}

