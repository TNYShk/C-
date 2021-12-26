/**********************************************
 * Task - Source Code                         *
 * Developer: Tanya                   		  *
 * 2021-12-  26                     		  *
 *                                            *
 *      Reviewed by    	 	  	 			  *
**********************************************/
#include <time.h> /*time_t */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert()         */
#include <string.h> /* memset         */

#include "task.h"




struct task
{
	task_func_t tsk_func;
	void *task_args;
	cleanup_func_t clean_func;
	void *cleanup_args;
	ilrd_uid_t uid;
	time_t time_to_run;
};


task_t *TaskCreate(task_func_t task_func, void *task_args, cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run)
{
	task_t *new_task = NULL;

	assert (task_func != NULL);
	assert (cleanup_func != NULL);

	new_task = (task_t *)malloc(sizeof(task_t));
	if(NULL ==new_task)
	{
		return NULL;
	}

	new_task->uid = UIDCreate();

	assert(!UIDIsSame(new_task->uid,UIDBadUID));

	new_task->time_to_run = time_to_run;
	new_task->tsk_func = task_func;
	new_task->clean_func = cleanup_func;
	
	new_task->task_args = task_args;
	new_task->cleanup_args = cleanup_args;
	
	return new_task;

}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	task->clean_func(task->cleanup_args);
	memset(task, 0, sizeof(task_t));
	
	free(task);
	task = NULL;
}

void TaskSetTimeToRun(task_t *task, time_t time_to_run)
{
	assert(NULL != task);

	task->time_to_run = time_to_run;
}


time_t TaskGetTimeToRun(const task_t *task)
{
	assert(NULL != task);

	return task->time_to_run;
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
	assert(NULL != task);
	
	return task->uid;
}


int TasksCompare(const void *task_1, const void *task_2)
{
	assert(NULL != task_1);
	assert(NULL != task_2);

	return (TaskGetTimeToRun((task_t*)task_1) - TaskGetTimeToRun((task_t*)task_2));

}


int TaskIsMatch(const task_t *task, ilrd_uid_t uid)
{
	assert(NULL != task);
	assert(!UIDIsSame(uid,UIDBadUID));

	return UIDIsSame(TaskGetUID(task), uid);
} 


int TaskRun(task_t *task)
{
	assert(NULL != task);

	return task->tsk_func(task->task_args);
} 