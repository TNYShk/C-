#ifndef __PTR_2_H__
#define __PTR_2_H__

const int aA;

	char * StrCpy(char* , const char * );
	char * StrnCpy(char *, const char *, size_t n);
	int StrCaseCmp(const char *, const char *);
	char * StrChr(const char *, int);
	size_t StrLen(const char *);
	char * StrDup(const char *);
	char * StrCat(char *, const char *);
	char * StrnCat(char *, const char *, size_t n);
	int StrnCmp (const char *,const char *);
	char * StrStr (const char *, const char *);
	size_t StrSpn(const char *, const char *);
	void isPalindrome(char*);


#endif
