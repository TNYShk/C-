/**********************************************
 * Towers of Hanoi quiz                       *
 * Tanya			                          *
 *          Jan 27, 2022                      *
 *                                            *
 * Reviewer:         	                      *
 **********************************************/
#include <stdio.h>    /* printf */



void towerofHanoi(int n, char from, char to, char aux_rod);
static const void *hash_func(const void *data);

int main()
{
    const void *hash;

    char *value = "tanya";

    hash = hash_func(value);
    printf("value %s turned to hash key: %ld\n", value, (*(size_t **)&hash));
    

    printf("\n 3 disks:\n");
    towerofHanoi(3 ,'A', 'C', 'B');
    /*printf("\n 4 disks:\n");
    towerofHanoi(4 ,'A', 'C', 'B');
    printf("\n 5 disks:\n");
    towerofHanoi(5 ,'A', 'C', 'B');*/
    return 0;
}


void towerofHanoi(int n, char from, char to, char aux_rod)
{
    if (n == 0)
    {
        return;
    }
        towerofHanoi(n -1, from, aux_rod , to);
        printf("Disk %d moved from %c to %c\n",n, from, to);
        towerofHanoi(n -1, aux_rod ,to, from);
    
}

static const void *hash_func(const void *key)
{
    size_t hash = 5381;
    int cc = 0;

    while (cc = (++(*(char *)&key)))
    {
        hash = ((hash << 5) + hash) + cc;
       
    }
    return *(void **)&hash;
}