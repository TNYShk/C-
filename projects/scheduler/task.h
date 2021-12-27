#ifndef __TASK_H__
#define __TASK_H__

#include <time.h>
#include "uid.h" 

/*action func, used for comparison between tasks */
typedef int (*task_func_t)(void *task_args);

typedef void (*cleanup_func_t)(void *cleanup_args);

typedef struct task task_t;


/*
 * DESCRIPTION: 
 * creates a new task based on provided params, task & cleanup funcs are given by user, and their responsibility to free (if) allocated memory!
 * 
 * 
 *
 * PARAMS: task & cleanup functions, their according arguments, and current time (in sec) 
 * 
 * RETURN: Pointer to the newly created task*/
task_t *TaskCreate(task_func_t task_func, void *task_args, cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run);

/*
 * DESCRIPTION: 
 * Destroys the task module
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: the task to destroy
 * 
 * RETURN: None    */
void TaskDestroy(task_t *task);

/*
 * DESCRIPTION: 
 * enables setting the time fot the task to run, will be the absolute time of running
 * 
 * PARAMS: task to edit, and the desired new time;
 * 
 * RETURN: None    */
void TaskSetTimeToRun(task_t *task, time_t time_to_run); 


/*
 * DESCRIPTION: 
 * time that the task is expected to run, in seconds
 * will be the absolute time of running
 * 
 * 
 *
 * PARAMS: task
 * 
 * RETURN: time (in seconds) that the task is expected to run*/
time_t TaskGetTimeToRun(const task_t *task);

/*
 * DESCRIPTION: 
 * each tasks, has a UID, this func returns it
 * 
 * 
 *
 * PARAMS: task to get it's UID
 * 
 * RETURN: UID of the task     */
ilrd_uid_t TaskGetUID(const task_t *task);


/*
 * DESCRIPTION: 
 * compares given tasks based on (priority) the set time to run.
 * 
 * PARAMS: tasks to compare
 * 
 * RETURN: zero- both tasks have same priority, positive number - task2 has higher prioruty. negative number - task1 is prior*/
int TasksCompare(const void *task_1, const void *task_2);

/*
 * DESCRIPTION: 
 * checks wether given UID matches task's UID
 * 
 * 
 * PARAMS: task and UID to compare
 * 
 * RETURN: 1 if the UID's match, otherwise 0        */
int TaskIsMatch(const task_t *task, ilrd_uid_t uid); 

/*
 * DESCRIPTION: 
 * Run Task
 * 
 * PARAMS: task to run
 * 
 * RETURN: -1 if failed. 0 SUCCESS */
int TaskRun(task_t *task); /*returns action_func return value*/

#endif /* __TASK_H__ */
