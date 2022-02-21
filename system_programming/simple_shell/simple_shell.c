/***********************************
 * Simple Shell - Source File      *
 * Developer: Tanya			       *
 *          Feb 17, 2022           *
 *                                 *
 * Reviewer: Gal T.                *
************************************/
#include <stdio.h> /* I/O funcs */
#include <stdlib.h> /*system() */
#include <string.h> /* strcmp */
#include <assert.h> /*assert */
#include <unistd.h> /* fork(), execvp*/
#include <sys/types.h>  /* pid_t */
#include <sys/wait.h> /* wait()*/
#include <errno.h> /* errno */


#include "simple_shell.h"


#define FAILURE (-1)
#define MAXLENG (4096)


int DoNothing(const char *str,const char *file)
{
	(void)str;
	(void)file;
	
	return EXIT;
}


int DoExit(char *dowhat, char *name)
{	
	(void)dowhat;
	(void)name;
	
	return EXIT;
}

int DoSystem(char *dowhat, char *name)
{	
	FILE *pFile;
	
	assert(NULL != dowhat);
	assert(NULL != name);

	pFile = fopen(name,"aw");
	write(STDOUT_FILENO, "In system()\n", 12);
	
	dowhat = fgets(dowhat, MAXLENG, stdin);
	fputs (dowhat,pFile);
	while (0 != strcmp("exit\n", dowhat))
	{
		system(dowhat);
		dowhat = fgets(dowhat, MAXLENG, stdin);
		fputs (dowhat,pFile);
	}
	fclose(pFile);
	memset(dowhat, 0, MAXLENG);
	return (EXIT != remove(name));
	
}


int DoFork(char *dowhat, char *name)
{	
	int status = 0;
	char **str_arr = NULL;
	char **head = NULL;
	FILE *pFile;

	assert(NULL != dowhat);
	assert(NULL != name);
	
	pFile = fopen(name,"aw");
     write(STDOUT_FILENO, "In fork()\n", 10);
    while (FORK)
    {
        dowhat = fgets(dowhat, MAXLENG, stdin);

        if(0 == strcmp("exit\n", dowhat))
        {
           	free(head);
           	remove(name);
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
                write(STDOUT_FILENO, "Invalid\n", 8);
                free(head);
                break;
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
