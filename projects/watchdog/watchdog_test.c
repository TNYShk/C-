#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "watchdog.h"

#define PRINT(msg)  do {write(STDOUT_FILENO, (msg), strlen(msg)); } while (0)

int main(int argc, char *argv[])
{
    time_t now = time(0);
    PRINT("DOG SITTER ON\n");
    assert(0 == WDStart(argc, argv));
    while(time(NULL) < now + 10);
    assert(0 == WDStop()); 
    PRINT("DOG SITTER OFF\n");
    PRINT("\tGREAT SUCCESS\n");

    return 0;
}


