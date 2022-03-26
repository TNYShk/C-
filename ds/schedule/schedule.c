/**********************************************
* Scheduler - Source Code                     *
* Developer: Tanya                   		  *
* 2021-12- 28                      		  	  *
*                                             *
*      Reviewed by Ori   	 	  	 	      *
* ********************************************/

#include <assert.h> /* assert 			  */
#include <stdlib.h> /* memory allocation, free */
#include <unistd.h> /* sleep */
#include <string.h> /*memset */
#include "scheduler.h"   /*scheduler API  */
#include "pq.h"			     /* priority queue API */
/* #include "utils.h" utilities lib      */ 


#define TIMEFAILURE ((time_t)-1)
#define TASK_NOT_FOUND (1)
#define OFF (0)
#define ON (1)
#define SUCCESS (0)

/* wrapper func*/
static int FindTask (const void *task, const void *uid);


struct scheduler
{
	pq_t* pq;
	int operate_flag;
};

scheduler_t *SchedCreate(void)
{
	scheduler_t *new_sched = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == new_sched)
	{
		return NULL;
	}

	new_sched->pq = PQCreate(&TasksCompare);
	if(NULL == new_sched->pq)
	{
		memset(new_sched, 0, sizeof(scheduler_t));
		free(new_sched);
		new_sched = NULL;
	}

	new_sched->operate_flag = OFF;

	return new_sched;
}

void SchedDestroy(scheduler_t *sched)
{
	assert(NULL != sched);

	SchedClear(sched);

	PQDestroy(sched->pq);
	sched->pq = NULL;
	
	memset(sched, 0, sizeof(scheduler_t));
	free(sched);
	sched = NULL;
}

ilrd_uid_t SchedAddTask(scheduler_t *sched, task_func_t task_func, void *task_args,
                        cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run)
{
	task_t *new_task = NULL;

	assert(NULL != sched);
	assert(NULL != task_func);
	assert(TIMEFAILURE != time_to_run);

	new_task = TaskCreate(task_func, task_args, cleanup_func, 
				     cleanup_args, time_to_run);

	if(NULL == new_task)
	{
		return UIDBadUID;
	}

	if(SUCCESS != PQEnqueue(sched->pq, new_task))
	{
		TaskDestroy(new_task);
		new_task = NULL;

		return UIDBadUID;	
	}

	return TaskGetUID(new_task);
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

	sched->operate_flag = OFF;

	while ((!SchedIsEmpty(sched)) && 
		  (return_status >= SUCCESS) && 
		  (OFF == sched->operate_flag))
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

	sched->operate_flag = ON;
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
