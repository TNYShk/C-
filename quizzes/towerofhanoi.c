/**********************************************
 * Towers of Hanoi quiz                       *
 * Tanya			                          *
 *          Jan 27, 2022                      *
 *                                            *
 * Reviewer:         	                      *
 **********************************************/
#include <stdio.h>    /* printf */



void towerofHanoi(int n, char from, char to, char aux_rod);


int main()
{

    towerofHanoi(3 ,'A', 'C', 'B');
    
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