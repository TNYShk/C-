#include <time.h>

#include <stdio.h> /* print */

#include "watchdog.h"



int main(int argc, char *argv[])
{
    time_t now = time(0);
    printf("status WD start: %d\n",WDStart(argc, argv));
    while(time(NULL) < now + 20);
    printf("stop is %d\n", WDStop()); 
  

    return 0;
}


