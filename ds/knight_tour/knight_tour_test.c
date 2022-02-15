#include <assert.h>
#include <stdio.h>

#include "knight_tour.h"

static void PrintMoves(unsigned char *tour);


int main(void)
{
    
	unsigned char idx = 1;
	unsigned char tour[64] = {0};

	KnightsTour(idx, tour);

	PrintMoves(tour);
    printf("\n");

    return 0;
}


static void PrintMoves(unsigned char *tour)
{
	int idx = 0;

	for (idx = 0; idx < 64 ; ++idx)
	{
		printf("->%d", tour[idx]);

		if(idx % 8 == 0)
		{
			printf("\n");
		}
	}
}

/*
/0 /1 /2 /3 /4 /5 /6 /7 /8 /9 /10 /11 /12 /13 /14 /15 /16 /17 /18 /19 /20 /21 /22 /23 /24 /25 /26 /27 /28 /29 /30
/31 /32 /33 /34 /35 /36 /37 /38 /39 /40 /41 /42 /43 /44 /45 /46 /47 /48 /49 /50 /51 /52 /53 /54 /55 /56 /57 /58
/59 /60 /61 /62 /63 */