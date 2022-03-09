#include <time.h>

#include <stdio.h> /* print */

#include "watchdog.h"



int main(int argc, char *argv[])
{
    time_t now = time(0);
    printf("ststus WD start: %d\n",WDStart(argc, argv));
    while(time(NULL) < now + 10);
    WDStop(); 
  

    return 0;
}


