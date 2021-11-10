#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "ptr_2.h"

int main(){

char* buffer=(char*)malloc(1000*sizeof(char));

char array2copy[]="Hello is this the right place?";
char bul[]="bullsh*t";
char tt[]="bla blak blad";
char tt1[]="tatyanQna";
char test= 'Q';
char test1[]= "Q";
char haystack[]= "need search for needle in a haystack";
char need[]= "needle";
const char mlc_ar[]="array_with_malloc";
char palindrome[]="AbbcbbA";
char palindrome2[]="1235321";

printf("original strspn: %ld\n",strspn(need,tt));
printf("My StrSpn: %ld\n",StrSpn(need,tt));
printf("original strspn: %ld\n",strspn(test1,tt1));
printf("My StrSpn: %ld\n",StrSpn(test1,tt1));

printf("(StrnCmp: %d)\n",StrnCmp(haystack,need));
printf("StStr: %s\n",StrStr(haystack,need));

isPalindrome(palindrome);
isPalindrome(palindrome2);

printf("%s\n",StrCpy(buffer,array2copy));
printf("buffer: %s\n",buffer);
printf("StrnCpy is: %s\n",StrnCpy(buffer,bul,8));



printf("StrCaseCmp of %s and %s is %d\n",tt,tt1,StrCaseCmp(tt,tt1));
printf("Strchar,will print from first occurance of %c in %s (if found), thus: %s\n",test,tt1,StrChr(tt1,test));


printf("strdup worked?yay!=> %s\n",StrDup(mlc_ar));


printf("StrnCat: %s\n",StrnCat(buffer,bul,10));

printf("StrCat: %s\n",StrCat(buffer,mlc_ar));





free(buffer);
return 0;
}

