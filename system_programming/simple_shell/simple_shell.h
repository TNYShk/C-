#ifndef __SIMPLE_SHELL_H__
#define __SIMPLE_SHELL_H__



typedef int (*compare_func)(const char *,const char *s);
typedef int (*action_func)(char *dowhat, char *name);

typedef enum status
{
    EXIT = 0,
    SYSTEM = 1,
    FORK = 2,
    NOTHING = 3,
    STATES
}status_t;


int DoNothing(const char *str,const char *file);
int DoExit(char *dowhat, char *name);
int DoSystem(char *dowhat, char *name);
int DoFork(char *dowhat, char *name);


#endif /* __SIMPLE_SHELL_H__*/

