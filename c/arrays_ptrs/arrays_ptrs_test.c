#include <stdio.h>  /*     standard library printf and what not  */
#include <stdlib.h> /*     malloc                                */
#include <assert.h> /*     test assertions made                  */
#include <string.h> /*     strlen strcopy and co.                */
#include <ctype.h>  /*     tolower                               */
#include <math.h>   /*     power of Josephus's choice            */

#include "arrays_ptrs.h"


#define MAXLEN 150
#define COL 3
#define ROW 3
#define MAXP 12


int main(int argc, char *argv[], char * envp[])
{

	int matrix[ROW][COL]= {{1,2,3},{7,8,9},{10,20,30}};
	int ans[ROW]= {0};
	char** buffer=NULL; 
	char ** env_ptr=NULL;
	int envp_counter=0;
	
	

	PrintMatrix(matrix);
	MatrixSum(matrix,ans);
	
	/* excercise 2 - Death of me */
	printf("\nJosephus Choice for %d soldiers is: %d\n",41,JosephusChoice(41));
	printf("\tJosephus Choice for %d soldiers is: %d\n",100,JosephusChoice(100));
	printf("\t\tJosephus Choice for %d soldiers is: %d\n",128,JosephusChoice(128));
	
	/*copied version of Josephus, causes STACK SMASH */
	/*
	int death[41]={0};
	printf("Josepus ver.2 %d\n",Josephus(death,41));
	printf("Josepus ver.2 %d\n",Josephus(death,100));
	printf("Josepus ver.2 %d\n",Josephus(death,128));
	*/
	
	/* excercise 3 - print data types */
	PrintTypes();


	/* excercise 4 - print envp */
	env_ptr=envp;
	while(*env_ptr++){
		envp_counter++;
	}

	buffer= (char**)calloc(envp_counter,sizeof(*envp));
	assert (NULL !=buffer);

	CopyEnvP(buffer,envp);
	free(buffer);

	(void) argc;
	(void) argv;
return 0;
}
