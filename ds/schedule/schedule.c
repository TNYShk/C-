/**********************************************
* Scheduler - Source Code                     *
* Developer: Tanya                   		  *
* 2021-12- 28                      		  	  *
*                                             *
*      Reviewed by Ori   	 	  	 	      *
* ********************************************/

#include <assert.h> /* assert 			  */
#include <stdlib.h> /* malloc, NULL ,free */
#include <unistd.h> /* sleep */

#include "scheduler.h"
#include "pq.h"			     /* priority queue API */
#include "utils.h" /* utilities lib      */

#define TIMEFAILURE ((time_t)-1)
#define TASK_NOT_FOUND (1)

static int FindTask (const void *task, const void *uid);


struct scheduler
{
	pq_t* pq;
	int stop_flag;
};

scheduler_t *SchedCreate(void)
{
	scheduler_t *sch = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == sch)
	{
		return NULL;
	}

	sch->pq = PQCreate(&TasksCompare);
	if(NULL == sch->pq)
	{
		free(sch);
		sch = NULL;
	}

	sch->stop_flag = FALSE;

	return sch;
}

void SchedDestroy(scheduler_t *sched)
{
	assert(NULL != sched);

	SchedClear(sched);

	PQDestroy(sched->pq);
	sched->pq = NULL;

	free(sched);
	sched = NULL;
}

ilrd_uid_t SchedAddTask(scheduler_t *sched, task_func_t task_func, void *task_args,
                        cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run)
{
	task_t *task_ptr = NULL;
	int enqueue_status = SUCCESS;

	assert(NULL != sched);
	assert(NULL != task_func);
	assert(TIMEFAILURE != time_to_run);

	task_ptr = TaskCreate(task_func, task_args, cleanup_func, 
				     cleanup_args, time_to_run);

	if(NULL == task_ptr)
	{
		return UIDBadUID;
	}

	enqueue_status = PQEnqueue(sched->pq, task_ptr);

	if(FAILURE == enqueue_status)
	{
		TaskDestroy(task_ptr);
		task_ptr = NULL;

		return UIDBadUID;	
	}

	return (TaskGetUID(task_ptr));
}

int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid)
{
	void *task_data = NULL;

	assert(NULL != sched);

	task_data = (task_t *)PQErase(sched->pq, &FindTask, &uid);

	if(NULL == task_data)	
	{
		return TASK_NOT_FOUND;
	}

	TaskDestroy(task_data);
	task_data = NULL;

	return SUCCESS;
}

int SchedRun(scheduler_t *sched)
{
	task_t *task = {0};
	int return_status = SUCCESS;

	assert(NULL != sched);

	sched->stop_flag = FALSE;

	while ((!SchedIsEmpty(sched)) && 
		  (return_status >= SUCCESS) && 
		  (FALSE == sched->stop_flag))
	{
		task = PQDequeue(sched->pq);

		while (TaskGetTimeToRun(task) > time(NULL)) 
		{
			sleep(TaskGetTimeToRun(task) - time(NULL));
		}

		return_status = TaskRun(task);

		if(return_status > SUCCESS)
		{
			TaskSetTimeToRun(task, time(NULL) + return_status);
			PQEnqueue(sched->pq, task);
		}
		else
		{
			TaskDestroy(task);
		}
	}
	return return_status;
}

void SchedStop(scheduler_t *sched)
{
	assert(NULL != sched);

	sched->stop_flag = TRUE;
}

size_t SchedSize(const scheduler_t *sched)
{
	assert(NULL != sched);

	return (PQSize(sched->pq));
}

int SchedIsEmpty(const scheduler_t *sched)
{
	assert(NULL != sched);

	return (PQIsEmpty(sched->pq));	
}

void SchedClear(scheduler_t *sched)
{
	void *task = NULL;

	assert(NULL != sched);

	while( !(PQIsEmpty(sched->pq)) )
	{
		task = PQDequeue(sched->pq);
		TaskDestroy(task);
	}	
}

static int FindTask (const void *task, const void *uid)
{
	assert(NULL != (task_t *)task);
	assert(NULL != (ilrd_uid_t *)uid);

	return (TaskIsMatch((task_t *)task, *(ilrd_uid_t *)uid));
}
