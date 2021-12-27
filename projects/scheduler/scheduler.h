#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "../task/task.h" 

typedef struct scheduler scheduler_t;

/*
 * DESCRIPTION: 
 * Creates a new Scheduler
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: None
 * 
 * RETURN: Pointer to the newly created Scheduler, otherwise NULL
 * Complexity: O(1) time, O(1) memory. */
scheduler_t *SchedCreate(void);

/*
 * DESCRIPTION: 
 * Destroy the Scheduler
 * 
 * Clears all tasks from the Scheduler, and destroys
 *
 * PARAMS: the Scheduler to destroy
 * 
 * RETURN: None
 * Complexity: O(n) time, O(1) memory. */
void SchedDestroy(scheduler_t *sched);

/*
 * DESCRIPTION: 
 * Add a new task based on provided params, to the scheduler
 * 
 * 
 *
 * PARAMS: 
 * *sched - pointer to the scheduler to add the task to
 * task_func - pointer to task's action func
 * void *task_args - pointer to the above required arguments
 * cleanup_func - pointer to task's cleanup func, called when task is erased, can be NULL
 * void *cleanup_args - pointer to the above needed arguments
 * time_to_run - absolutr timr (in seconds), for task to start at.
 * 
 * RETURN: UID of the newly created task   
 * Complexity: O(1) time, O(1) memory. */
ilrd_uid_t SchedAddTask(scheduler_t *sched, task_func_t task_func, void *task_args,
                        cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run);

/*
 * DESCRIPTION: 
 * Removes according task from the scheduler
 * 
 * PARAMS: 
 * *sched - pointer to the scheduler to work on
 * uid - UID of the task to remove

 * 
 * RETURN: 1 if SUCCESS,
 * Complexity: O(n) time, O(1) memory. */
int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid);

/*
 * DESCRIPTION: 
 * Run tasks in the Scheduler, doesnt stop unless a specific stopping function is provided!
 * 
 * PARAMS: 
 * *sched - pointer to the scheduler to work on
 * 

 * 
 * RETURN: 0 SUCCESS,
 * Complexity: O(....) time, O(1) memory. */
int SchedRun(scheduler_t *sched);

/*
 * DESCRIPTION: 
 * Stops running of the scheduler
 * 
 * PARAMS: 
 * *sched - pointer to the scheduler to work on
 * 

 * 
 * RETURN: None
 * Complexity: O(1) time, O(1) memory. */
void SchedStop(scheduler_t *sched);

/*
 * DESCRIPTION: 
 * Counts amount of tasks in the scheduler
 * 
 * PARAMS: 
 * *sched - pointer to the scheduler to work on
 * 

 * 
 * RETURN: number of current tasks in scheduler
 * Complexity: O(n) time, O(1) memory. */
size_t SchedSize(const scheduler_t *sched);

/*
 * DESCRIPTION: 
 * Boolean check if the scheduler is empty (no tasks)
 * 
 * PARAMS: 
 * *sched - pointer to the scheduler to work on
 * 

 * 
 * RETURN: 1 if Empty, otherwise not empty
 * Complexity: O(1) time, O(1) memory. */
int SchedIsEmpty(const scheduler_t *sched);

/*
 * DESCRIPTION: 
 * clears all tasks from the scheduler
 * clears tasks allocated memory as well, but not scheduler's!
 * ! dont forget to clear scheduler's allocated memory!
 * 
 * PARAMS: 
 * *sched - pointer to the scheduler to work on
 * 
 * 
 * RETURN: None
 * Complexity: O(n) time, O(1) memory. */
void SchedClear(scheduler_t *sched);

#endif /* __SCHEDULER_H__ */
