#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ZERO (0)
#define COL (7)
#define LIN (6)

int FindMissingNum(int *arr, int length);
static void PrintMap(int (*matrix)[7]);
int IsInsideShape(int (*matrix)[7], int x, int y);

int main(void)
{
	int array[1025] = {0};
	int bitmap[LIN][COL] = {0};
	int i = 0;
	int length = 0;

	length = sizeof(array)/sizeof(array[0]);
	
	for (i = 0; i < length; ++i)
	{
		array[i] = i;
	}
	array[26] = 0;
	printf("missing num is %d\n", FindMissingNum(array, length));
	
	/*BitMap initialize shape*/
	bitmap[1][3] = 1;
	bitmap[2][2] = 1;
	bitmap[2][4] = 1;
	bitmap[3][1] = 1;
	bitmap[3][5] = 1;
	bitmap[4][1] = 1;
	bitmap[4][2] = 1;
	bitmap[4][3] = 1;
	bitmap[4][4] = 1;
	bitmap[4][5] = 1;
	bitmap[5][1] = 1;
	bitmap[5][5] = 1;
	
	PrintMap(bitmap);
	printf("\nis point(%d,%d) inside?\n",3,2);
	( IsInsideShape(bitmap, 3,2) == 0 ? printf("yes!\n"): printf("no!\n"));
	bitmap[3][2] = 0;
	printf("\nis point(%d,%d) inside?\n",5,2);
	( IsInsideShape(bitmap, 5,2) == 0 ? printf("yes!\n"): printf("no!\n"));
	bitmap[5][2] = 0;
	printf("\nis point(%d,%d) inside?\n",2,6);
	( IsInsideShape(bitmap, 2,6) == 0 ? printf("yes!\n"): printf("no!\n"));
	return 0;
}

static void PrintMap(int (*matrix)[COL])
{
	int i = 0, j = 0;
	printf("Bitmap 2D array elements:\n");

	for(i=0; i < LIN; ++i) 
	{
      for(j = 0; j < COL; ++j) 
      {
        printf(" %d ", matrix[i][j]);
        if(j== LIN)
        {
           printf("\n");
        }
      }
	}
}

int IsInsideShape(int (*matrix)[COL], int x, int y)
{
	int column = 0, counter = 0;
	if(matrix[x][y] == 1)
	{
		return 0;
	}
	matrix[x][y] = 5;

	for(; column < y; ++column)
	{
		if(matrix[x][column] == 1)
		{
			++counter;
		}
	}
	if(counter % 2 != 0)
	{
		int line = 0;
		for(counter = 0; column < COL; ++column)
		{
			if(matrix[x][column] == 1)
			{
				++counter;
			}
		}
		
		if(counter % 2 == 0)
		{
			PrintMap(matrix);
			return 1;
		}

		for(counter = 0; line < x; ++line)
		{
			if(matrix[line][y] == 1)
			{
			++counter;
			}
		}
		if(counter % 2 == 0)
		{
			PrintMap(matrix);
			return 1;
		}
		for(counter = 0; line < LIN; ++line)
		{
			if(matrix[line][y] == 1)
			{
				++counter;
			}
		}

		PrintMap(matrix);
		return (counter % 2 == 0);
	}
	PrintMap(matrix);	
	return 1;
}



int FindMissingNum(int *arr, int length)
{
	int total = 0, i = 0;

	assert(NULL != arr);

	total = ((length - 1) / 2) * (length);
	
	for(; i< length; ++i)
	{
		total -= arr[i];
	}
	return total;
}