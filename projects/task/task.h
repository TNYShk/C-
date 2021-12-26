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
 * creates a new task based on provided params, task & cleanup funcs are given by user, and their responsibility to free (if) allocated memory in them!
 * 
 * 
 *
 * PARAMS: task & cleanup functions, their according arguments, and current time (in sec) 
 * 
 * RETURN: Pointer to the newly created task*/
task_t *TaskCreate(task_func_t task_func, void *task_args, cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run);

/*
 * DESCRIPTION: 
 * Destroys the task
 * 
 * !don't forget to free allocated memory!
 *
 * PARAMS: the task to destroy
 * 
 * RETURN: None*/
void TaskDestroy(task_t *task);

/*
 * DESCRIPTION: 
 * set desired start time for the task
 * 
 * 
 *
 * PARAMS: task to edit, and the desired new time;
 * 
 * RETURN: Pointer to the newly created dll, otherwise NULL*/
void TaskSetTimeToRun(task_t *task, time_t time_to_run); 
/*will be the absolute time of running (as per the previous time/new time of performance[APOCH])*/

/*
 * DESCRIPTION: 
 * time that the task is expected to run, in seconds
 * 
 * 
 *
 * PARAMS: task
 * 
 * RETURN: time (in seconds) that the task is expected to run*/
time_t TaskGetTimeToRun(const task_t *task);

/*
 * DESCRIPTION: 
 * each tasks, has a UID, this func returns its details
 * 
 * 
 *
 * PARAMS: task
 * 
 * RETURN: UID struct of the task*/
ilrd_uid_t TaskGetUID(const task_t *task);


/*
 * DESCRIPTION: 
 * compares given tasks based on (priority) the set time to run.
 * 
 * 
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
 * RETURN: 1 if the UID's match, otherwise 0*/
int TaskIsMatch(const task_t *task, ilrd_uid_t uid); 

/*
 * DESCRIPTION: 
 * Run Task
 * 
 * 
 *
 * PARAMS: task to run
 * 
 * RETURN: -1 if failed. 0 SUCCESS */
int TaskRun(task_t *task); /*returns action_func return value*/

#endif /* __TASK_H__ */
