/***********************************
 * Simple Shell Test- Source File      *
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


#include "simple_shell.h"

#define MAXLENG (4096)
#define FAILURE (-1)

typedef struct shell shell_t;


struct shell
{
    char *name;
    compare_func cmp;
    action_func action;
};



static void InitStruct(shell_t *array);




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