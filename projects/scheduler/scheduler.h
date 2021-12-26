#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "../task/task.h" 

typedef struct scheduler scheduler_t;

scheduler_t *SchedCreate(void);

void SchedDestroy(scheduler_t *sched);


ilrd_uid_t SchedAddTask(scheduler_t *sched, task_func_t task_func, void *task_args,
                        cleanup_func_t cleanup_func, void *cleanup_args, time_t time_to_run);


int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t uid);


int SchedRun(scheduler_t *sched);


void SchedStop(scheduler_t *sched);


size_t SchedSize(const scheduler_t *sched);


int SchedIsEmpty(const scheduler_t *sched);

void SchedClear(scheduler_t *sched);

#endif /* __SCHEDULER_H__ */
