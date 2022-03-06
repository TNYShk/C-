#include "time.h"

#include "watchdog.h"

int main(int argc, char *argv[])
{
    time_t start = time(NULL);

    WDStart(argc, argv);

  

    return 0;
}


