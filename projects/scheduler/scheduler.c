/**********************************************
 * Scheduler - Source Code                    *
 * Developer: Tanya                   		  *
 * 2021-12-                       		  	  *
 *                                            *
 *      Reviewed by    	 	  	 			  *
**********************************************/
#include <time.h> /*time_t */
#include <stdlib.h> /* memory allocation  */
#include <assert.h> /* assert()         */
#include <string.h> /* memset         */


#include "scheduler.h" 
#include "priority_queue.h"

#define FAIL (-1)

struct scheduler
{
	pq_t *pq;
};


scheduler_t *SchedCreate(void)
{
    scheduler_t *new_sched = NULL;

    new_sched = (scheduler_t *)malloc(sizeof(scheduler_t));
    new_sched->pq = PQCreate(&TasksCompare);

    if (NULL == new_sched || NULL == new_sched->pq)
    {
        free(new_sched);
        new_sched = NULL;
    }

    return new_sched;
}

void SchedDestroy(scheduler_t *sched)
{
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
    assert(NULL != cleanup_func);
    assert((time_t)FAIL != time_to_run);

    new_task = TaskCreate(task_func, task_args, cleanup_func, cleanup_args, time_to_run);

    if(!!PQEnqueue(sched->pq, new_task))
    {
        TaskDestroy(new_task);
        SchedDestroy(sched);
    }

    return TaskGetUID(new_task);

}

int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid)
{
    
    assert(NULL != sched);
    assert(UIDIsSame(UIDBadUID, uid));
}