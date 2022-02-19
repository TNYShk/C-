/***********************************
 * Simple Shell - Source File      *
 * Developer: Tanya			       *
 *          Feb 17, 2022           *
 *                                 *
 * Reviewer:  	                   *
************************************/
#include <stdio.h> /* I/O funcs */
#include <stdlib.h> /*system() */
#include <string.h> /* strcmp */
#include <assert.h> /*assert */
#include <unistd.h> /* fork(), execvp*/
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h> /* wait()*/
#include <errno.h> /* errno */

#define FAILURE (-1)

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
	NOTHING = 3,
	STATES
}status_t;


static void InitStruct(shell_t *array);
int DoExit(char *dowhat, char *name);
int DoSystem(char *dowhat, char *name);
int DoFork(char *dowhat, char *name);
int DoNothing(const char *str,const char *file);


int main (int argc, char *argv[])
{
	static shell_t shelly[STATES] = {0};
	static char sentence[MAXLENG] = {0};
	status_t run_flag = SYSTEM;
	
	if(NULL == argv[1])
	{	
		printf("please provide a name\n");
		return EXIT;
	}

	InitStruct(shelly);

	while(run_flag)
	{
		int i = 0;
		fgets(sentence, MAXLENG, stdin);

		for( i = 0; i < STATES; ++i)
		{
			if (0 == shelly[i].cmp(shelly[i].name,sentence))
			{
				run_flag = shelly[i].action(sentence,argv[1]);

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

	array[NOTHING].name = " ";
	array[NOTHING].cmp = DoNothing;
	array[NOTHING].action = DoFork;


}

int DoNothing(const char *str,const char *file)
{
	(void)str;
	(void)file;
	
	return EXIT;
}


int DoExit(char *dowhat, char *name)
{	
	(void)dowhat;
	
	return (EXIT != remove(name));
}

int DoSystem(char *dowhat, char *name)
{	
	FILE *pFile;
	status_t return_value = 0;

	assert(NULL != dowhat);
	assert(NULL != name);

	pFile = fopen(name,"aw");
	
	printf("In System, enter commands:\n");

	dowhat = fgets(dowhat, MAXLENG, stdin);

	while (0 != strcmp("exit\n", dowhat))
	{
		return_value = system(dowhat);
		dowhat = fgets(dowhat, MAXLENG, stdin);
		fputs (dowhat,pFile);
	}
	fclose(pFile);
	memset(dowhat, 0, MAXLENG);
	return return_value;
	
}





int DoFork(char *dowhat, char *name)
{	
	int status = 0;
	char **str_arr = NULL;
	char **head = NULL;
	FILE *pFile;

	assert(NULL != dowhat);

	pFile = fopen(name,"aw");
    
    while (FORK)
    {
        printf("Fork, enter commands:\n");

        dowhat = fgets(dowhat, MAXLENG, stdin);

        if(0 == strcmp("exit\n", dowhat))
        {
            break;
        }
        fputs (dowhat,pFile);

        str_arr = (char **)calloc(strlen(dowhat), sizeof(char *));
        if (NULL == str_arr)
        {
        	errno;
        	fprintf(pFile,"error no: %d\n",errno);
        	break;
        }

        head = str_arr;
        
        *str_arr++ = strtok(dowhat, " \n");
        while (NULL != (*str_arr++ = strtok(NULL, " \n")));
       

        if (0 == fork())
        {
            errno = 0;
            if (FAILURE == execvp(*head, head) && errno != 0)
            {
                fprintf(pFile,"error no: %d\n",errno);
                printf("Invalid\n");
            }
        }
        else
        {
            wait(&status);
        }
        free(head);
        head = NULL;
    }

 	fclose(pFile);
 	memset(dowhat, 0, MAXLENG);
    return 0;
}
