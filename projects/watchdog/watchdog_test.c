#include <time.h>
#include <unistd.h>
#include "watchdog.h"
#include <string.h> 
#include <stdlib.h> /* atoi */
#include <stdio.h> /* print */




int main(int argc, char *argv[])
{
   
    WDStart(argc, argv);
    sleep(6);
    WDStop();
  

    return 0;
}


