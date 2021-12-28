/**********************************************
* Scheduler - Source Code                     *
* Developer: Tanya                   		  *
* 2021-12- 28                      		  	  *
*                                             *
*      Reviewed by    	 	  	 			  *
**********************************************/
#include <time.h>   /*time_t             */
#include <stdlib.h> /* memory allocation*/
#include <assert.h> /* assert          */
#include <string.h> /* memset         */
#include <unistd.h> /* sleep         */


#include "task.h" /*task related header  */
#include "scheduler.h" /*scheduler header  */
#include "priority_queue.h" /* for the scheduler */

enum status
{
    FAIL = -1,
    OK,
    NEXT
};


struct scheduler
{
	pq_t *pq;
    int run_flag;
};

/*wrapper func */
static int TaskMatchs(const void *task, const void *uid);
/************* */


scheduler_t *SchedCreate(void)
{
    scheduler_t *new_sched = NULL;

    new_sched = (scheduler_t *)malloc(sizeof(scheduler_t));
    new_sched->pq = PQCreate(&TasksCompare);

    if (NULL == new_sched || NULL == new_sched->pq)
    {
        memset(new_sched, 0, sizeof(scheduler_t));
        free(new_sched);
        free(new_sched->pq);

        new_sched = NULL;
        new_sched->pq = NULL;  
    }
    else
    {
        new_sched->run_flag = OK;
    }
    return new_sched;
}

void SchedDestroy(scheduler_t *sched)
{
    assert(NULL != sched);

    SchedClear(sched);
    PQDestroy(sched->pq);
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

    new_task = TaskCreate(task_func, task_args, cleanup_func, cleanup_args, time_to_run);
    
    if(NULL == new_task)
    {
        return UIDBadUID;
    }
    if(OK != PQEnqueue(sched->pq, new_task))
    {
        TaskDestroy(new_task);
        new_task = NULL;
    }
    return TaskGetUID(new_task);
}


int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid)
{
    task_t *to_remove = NULL;

    assert(NULL != sched);
    assert(!UIDIsSame(UIDBadUID, uid));

    to_remove = PQErase(sched->pq, &TaskMatchs, &uid);
    
    if(NULL != to_remove)
    {
        TaskDestroy(to_remove);
        to_remove = NULL;
    }
   return (NULL == to_remove);
}

size_t SchedSize(const scheduler_t *sched)
{
    assert(NULL != sched);

    return PQSize(sched->pq);
}


int SchedIsEmpty(const scheduler_t *sched)
{
    assert(NULL != sched);

    return PQIsEmpty(sched->pq);
}

void SchedClear(scheduler_t *sched)
{
    assert(NULL != sched);
    
    while (!SchedIsEmpty(sched))
    {
        TaskDestroy(PQDequeue(sched->pq));
    }
}

int SchedRun(scheduler_t *sched)
{
    int status = FAIL;
    time_t now = time(0);
    task_t *temp = NULL;

    assert(NULL != sched);

    sched->run_flag == NEXT;

    while(!SchedIsEmpty(sched) && (!sched->run_flag))
    {
        task_t *running = PQPeek(sched->pq);

        if (TaskGetTimeToRun(running) > now)
        {
            sleep(TaskGetTimeToRun(running) - now);
        }
        
        temp = PQDequeue(sched->pq);
        status = TaskRun(running);
      
        if(OK > status)
        {
            TaskDestroy(temp);
            temp = NULL;
            sched->run_flag == OK;
        }
        else if (OK == status)
        {
            TaskDestroy(temp);
            temp = NULL; 
        }
        else
        {
            TaskSetTimeToRun(temp, TaskGetTimeToRun(temp) + status);
            status = PQEnqueue(sched->pq, temp);
        }
    }   
    return status;
}




/* wrapper func*/
static int TaskMatchs(const void *task, const void *uid)
{
    return TaskIsMatch((const task_t *)task, *((ilrd_uid_t *)uid));
}