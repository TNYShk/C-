#include "time.h"
#include "unistd.h"
#include "watchdog.h"

int main(int argc, char *argv[])
{
    

    WDStart(argc, argv);
    sleep(3);
    WDStop();
  

    return 0;
}


