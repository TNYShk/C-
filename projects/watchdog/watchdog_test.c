#include <time.h>
#include <unistd.h>
#include "watchdog.h"
#include <string.h> 
#include <stdlib.h> /* atoi */
#include <stdio.h> /* atoi */
#define ARGZ (256)
#define PATHNAME ("/kickdog")



int main(int argc, char *argv[])
{
   
    WDStart(argc, argv);
    sleep(5);
    WDStop();
  

    return 0;
}


