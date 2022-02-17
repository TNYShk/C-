/***********************************
 * Simple Shell - Source File      *
 * Developer: Tanya			       *
 *          Feb 17, 2022           *
 *                                 *
 * Reviewer:  	                   *
************************************/
#include <stdio.h> /*for all I/O funcs */
#include <stdlib.h> /*size_t */
#include <string.h> /* strcmp */
#include <assert.h> /*assert */
#include <unistd.h>
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h>
#include <errno.h> /* errno */

typedef int (*compare_func)(const char *,const char *s);
typedef int (*action_func)(char *dowhat, char *name);

#define MAXLENG (4096)





typedef struct shell
{
	char *name;
	compare_func cmp;
	action_func action;

}shell_t;


typedef enum status
{
	EXIT = 0,
	SYSTEM = 1,
	FORK = 2,
	STATES
}status_t;


static void InitStruct(shell_t *array);
int DoExit(char *dowhat, char *name);
int DoSystem(char *dowhat, char *name);
int DoFork(char *dowhat, char *name);



int main (int argc, char *argv[])
{
	
	static shell_t shelly[STATES] = {0};
	static char sentence[MAXLENG];
	status_t run_flag = SYSTEM;
	
	char *operation = NULL;
	if(NULL == argv[1])
	{	
		printf("try again!\n");
		return 0;
	}

	operation = argv[1];

	InitStruct(shelly);

	while(run_flag)
	{
		int i = 0;
		fgets(sentence, MAXLENG, stdin);

		for( i = 0; i < STATES; ++i)
		{
			if (0 == shelly[i].cmp(shelly[i].name,sentence))
			{
				run_flag = shelly[i].action(sentence,operation);

				break;
			}
		}
	}
	(void)argc;

	return 0;
}


static void InitStruct(shell_t *array) 
{	
	array[EXIT].name = "exit\n";
	array[EXIT].cmp = strcmp;
	array[EXIT].action = DoExit;

	array[SYSTEM].name = "system\n";
	array[SYSTEM].cmp = strcmp;
	array[SYSTEM].action = DoSystem;

	array[FORK].name = "fork\n";
	array[FORK].cmp = strcmp;
	array[FORK].action = DoFork;


}




int DoExit(char *dowhat, char *name)
{	
	(void)dowhat;
	(void)name;
	return EXIT;
	
}

int DoSystem(char *dowhat, char *name)
{	
	
	int return_value = 1;
	(void)name;
	assert(NULL != dowhat);
	printf("In System, enter commands:\n");

	dowhat = fgets(dowhat, MAXLENG, stdin);

	while (0 != strcmp("exit\n", dowhat))
	{
		return_value = system(dowhat);
		dowhat = fgets(dowhat, MAXLENG, stdin);
	}
	
	return return_value;
	
}


int DoFork(char *dowhat, char *name)
{	
	int status = 0;
	char **str_arr = NULL;
	char **head = NULL;
	(void)name;

	assert(NULL != dowhat);

    while (1)
    {
        printf("enter an input\n");

        dowhat = fgets(dowhat, MAXLENG, stdin);
        if(0 == strcmp("exit\n", dowhat))
        {
            break;
        }
        
        str_arr = (char **)calloc(strlen(dowhat), sizeof(char *));
        if (NULL == str_arr)
        	return -1;

        head = str_arr;
        
        *str_arr++ = strtok(dowhat, " \n");
        
        while (NULL != (*str_arr++ = strtok(NULL, " \n")));
       

        if (0 == fork())
        {
            errno = 0;
            if (-1 == execvp(*head, head) && errno != 0)
            {
                printf("failed, errno = %d \n", errno);
            }
        }
        else
        {
            wait(&status);
        }
        free(head);
        head = NULL;

    }


    return 0;
}