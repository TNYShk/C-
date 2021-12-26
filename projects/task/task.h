#ifndef __TASK_H__
#define __TASK_H__

#include <time.h>
#include "uid.h" 

typedef int (*task_func_t)(void *task_args);

typedef void (*cleanup_func_t)(void *cleanup_args);

typedef struct task task_t;

task_t *TaskCreate(task_func_t task_func, void *task_args, cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run);

void TaskDestroy(task_t *task);

void TaskSetTimeToRun(task_t *task, time_t time_to_run); 
/*will be the absolute time of running (as per the previous time/new time of performance[APOCH])*/

/* get time to run */
time_t TaskGetTimeToRun(const task_t *task);

ilrd_uid_t TaskGetUID(const task_t *task);

/*gets send to PQ, doees the insert based on cmp func */
int TasksCompare(const void *task_1, const void *task_2);

int TaskIsMatch(const task_t *task, ilrd_uid_t uid); 

/*starts the process, then it goes up to compare/match */
int TaskRun(task_t *task); /*returns action_func return value*/

#endif /* __TASK_H__ */
