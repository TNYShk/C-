/**********************************
 * Knights - C File               *
 * Developer: Tanya               *
 * Written:   15/02/2022          *
 *                                *
 * Reviewer:                      *
 **********************************/
#include <assert.h> /* asserts*/
#include <stdio.h> /*Printing */
#include <string.h> /* memset() */

#include "knight_tour.h" /* program header*/

void PrintMoves(unsigned char *tour);
void TestWarnsdorff();
void TestKnight();

int main(void)
{
	
    TestWarnsdorff();
      /*dont run
     TestKnight();*/
   	
    return 0;
}

void TestWarnsdorff()
{
    int i = 0;
    unsigned char idx = 63;	
    unsigned char tour[64] = {0};
    Warnsdorff(idx, tour);
    PrintMoves(tour);

    for(i = 62; i >= 0; --i)
    {
    	printf("\n\nidx %d\n", i);
    	memset(tour, 0 , sizeof(size_t) * sizeof(size_t));
    	Warnsdorff(i, tour);   
    	PrintMoves(tour);
    }
    printf("\n");


   

}

void TestKnight()
{

	unsigned char idx = 1;
	unsigned char tour[64] = {0};

	KnightsTour(idx, tour);

	PrintMoves(tour);
    printf("\n");

}



void PrintMoves(unsigned char *tour)
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

