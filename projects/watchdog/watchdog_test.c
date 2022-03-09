#include <time.h>
#include <unistd.h>
#include "watchdog.h"
#include <string.h> 
#include <stdlib.h> /* atoi */
#include <stdio.h> /* print */




int main(int argc, char *argv[])
{
    time_t now = time(0);
    WDStart(argc, argv);
    while(time(NULL) < now + 20);
    WDStop(); 
  

    return 0;
}


