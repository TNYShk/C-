#include <assert.h>
#include <stdio.h>

#include "knight_tour.h"

static void PrintMoves(unsigned char *tour);


int main(void)
{
    
	unsigned char idx = 27;
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

		if(idx % 2 == 0)
		{
			printf("\n");
		}
	}
}
