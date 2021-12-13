#include <string.h>
#include <stdio.h>

enum states{SUCCESS,FAIL};

int isRotation(const char *s1, const char *s2)
{
	char spotter = *s1;
	char *cut_here_s2 = strchr(s2, spotter);
	
	while(cut_here_s2)
	{
		size_t leng= strlen(cut_here_s2);
		if (0==(strncmp(cut_here_s2,s1,leng))&&
		   (0==strncmp(s2,s1+leng,strlen(s2) - leng)))
		{
			return SUCCESS;
		}
		else
		{
			cut_here_s2 = strchr(cut_here_s2 + 1,spotter);
		}
	}
	return FAIL;	
}



int main()
{
	const char s1[]="121234";
	const char s2[]="123412";
	if(SUCCESS==isRotation(s1,s2))
		printf("great Success, %s & %s is rotation\n",s1,s2);
	
	/*
	char * ps1;
	char * ps2;
	char * ps3;
	char *ps4;
	size_t i=0;
	size_t slength= strlen(s1);
	size_t length=0;
	ps1= s1;
	ps2= s2;
	printf("ps1 is %s\n",ps1);
	printf("ps2 is %s\n",ps2);

	ps3= ps2+slength-1; 
	printf("ps3 = ps2+slength-1; is %s\n",ps3);
	ps4= strchr(ps2,*ps1);
	printf("ps4 is %s\n",ps4);
	while(*ps4)
	{
		ps4= strchr(ps2,*ps1);
		length=ps3-ps4;
		if ((strncmp(ps1,ps4,length)) && (strncmp(ps1+length,ps4,length)) ==0)
		{
			i=999;
			break;
		}
		else
			ps1++;	
	}		
	printf(" i is %ld\n",i);
	*/
	return 0;
}
