#include <stdio.h> /*for all I/O funcs */
#include <stdlib.h> /*size_t */
#include <string.h> /* strcmp */
#include <assert.h> /*assert */
#define MAX (4000)

/* PSEUDOCODE
get filename as input from user
./a.out filename
create a FILE with according name
create structures,
create array of sctrucs 
initialize structs

while (! exit){
	get string input from user
	compare to structure headers
	if users string == one the headers{
	fo to the action function of the structure
	}
	else
	write string to file

*/


typedef int (*foo)(const char *,const char *s);
typedef int (*barf)(char *s, char *filename);


typedef struct Death{

	char* name;
	foo compare;
	barf action;
} Death;

enum struname{Exit,Remove,Count,ToBegin,Write,FIVE};



int DoExit(char *, char *);
static void InitStruct(Death *);
FILE* GetFile(char *argv[]);
int DoNothing(const char *str,const char *file);
int AddtoStart(char*,char*);
static int CompareChar(const char* str, const char* ch);
int fCopy(FILE * ,FILE *);



int main(int argc, char *argv[])
{
	
	int isRunning=1;
	static char sentence[MAX];
	static Death array[FIVE];
	
	char *filename;
	if(NULL ==argv[1]){
		printf("restart! forgot file name\n");
		return 0;
	}

	filename= argv[1];

	InitStruct(array);
	
	while(isRunning)
	{ 
		int i;
		fgets (sentence,MAX,stdin);
		
		for(i=0;i<FIVE;i++)
		{ 
			if(0 == array[i].compare(array[i].name,sentence))
			{
				isRunning=array[i].action(sentence,filename);

				break;
			}
		}
	}
	(void) argc;

	return 0;			
}			
	

int doWrite(char *s, char *file)
{
	FILE * pFile;
	assert (NULL != file);
	pFile = fopen (file,"a");
	fputs (s,pFile);
	fclose(pFile);
	return 1;
}


int DoExit(char *str, char *file){
	
	(void)str;
	(void)file;
	return 0;
}


int DoRemove(char *str, char *file)
{
	int ans;
	(void)str;
	ans =remove(file);
	return (0 == ans);
}


int DoNothing(const char *str,const char *file)
{
	(void)str;
	(void)file;
	return 0;
}


int CountLines(char *sent,char* file)
{
	char cc;
	int count=0;
	FILE * pFile;
	pFile = fopen (file,"r");
	if(NULL != pFile){
	for(cc= getc(pFile); cc!=EOF; cc=getc(pFile))
	{
		if ('\n' == cc)
		{
			++count;
		}
	}
	fclose(pFile);
	printf("num of newlines %d\n",count);
	}
	(void)sent;
	return 1;
}


static int CompareChar(const char * str, const char * ch)
{
	if(*str==*ch)
		return 0;
	return 1;
}



int AppendtoStart(char*string,char*file)
{
	FILE * pFile;
	FILE * cFile;
	assert (NULL != file);
	pFile = fopen (file,"r+");
	cFile= fopen("new_file","a+");
	fputs (++string,cFile);
	
	if(0==fCopy(pFile,cFile)){
		fclose(pFile);
		fclose(cFile);
		remove(file);
		rename("new_file", file);
		return 1;
	}
	fclose(pFile);
	fclose(cFile);
	return 0;
}


int fCopy(FILE * fsrc,FILE *fdest)
{
	char buffer[MAX];
	size_t len;
	while((len = fread(buffer,sizeof(char), sizeof(buffer),fsrc)) >0)
	{
		if(fwrite(buffer,sizeof(char), len, fdest) != len)
			return EOF;
	}
	if (ferror(fsrc) || ferror(fdest))
		return EOF;
	return 0;
}
	

static void InitStruct(Death * array) /*pointer to struct of type death*/
{	
	array[Exit].name="-exit\n";
	array[Exit].compare= strcmp;
	array[Exit].action= DoExit;

	array[Remove].name="-remove\n";
	array[Remove].compare= strcmp;
	array[Remove].action= DoRemove;

	array[Count].name="-count\n";
	array[Count].compare=strcmp;
	array[Count].action=CountLines;

	array[3].name="<";
	array[3].compare=CompareChar;
	array[3].action=AppendtoStart;

	array[Write].name=" ";
	array[Write].compare=DoNothing;
	array[Write].action=doWrite;

}



/*
FILE* GetFile(char *argv[])
{
	FILE * pFile;
	char filename[100];
	if(argv[1])
	{
		pFile = fopen (argv[1],"aw");
		printf("%s\n",argv[1]);
	}
	else
	{
		printf ("Enter desired filename: \n");
		fgets(filename,100, stdin);
		printf("%s\n",filename);
		pFile = fopen (filename,"aw");
	}
	return pFile;
}
*/
