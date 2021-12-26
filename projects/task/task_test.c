#include <time.h> /*time_t */
#include <stdio.h> /*printf */
#include <assert.h> /* assert()         */


#include "task.h"


int TaskAction(void *task_args)
{
	void *ptr = task_args;
	printf("int arg is %d\n", *(int *)ptr);
	return 0;
}

void Clean(void *cleanup_args)
{
	cleanup_args = NULL;
}









int main(void)
{
	int x = 26;
	task_t *test = NULL;
	time_t now = time(NULL);
	test = TaskCreate(&TaskAction, &x, &Clean, &x, time(NULL));
	printf("time: %lu\n", TaskGetTimeToRun(test));
	TaskSetTimeToRun(test, now + 600);
	printf("time set: %lu\n", TaskGetTimeToRun(test));
	TaskRun(test);

	TaskDestroy(test);

	return 0;
}