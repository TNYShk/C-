#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "ptr_2.h"

int main(){

char* buffer=(char*)malloc(1000*sizeof(char));

char array2copy[]="Hello is this the right place?";
char bul[]="bullsh*t";
char tt[]="Tatyanna";
char tt1[]="tatyanQna";
char test= 'Q';
char test1[]= "Q";
char haystack[]= "need search for needle in a haystack";
char need[]= "needle";
const char mlc_ar[]="array_with_malloc";
char palindrome[]="AbbcbbA";
char palindrome2[]="12376321";
char palindrome3[]="!123&5&321!";
char *ptr_ch;


printf("original strspn: %ld\n",strspn(need,tt));
printf("My StrSpn: %ld\n",StrSpn(need,tt));
printf("original strspn: %ld\n",strspn(test1,tt1));
printf("My StrSpn: %ld\n\n",StrSpn(test1,tt1));

printf("StStr: %s\n",StrStr(haystack,need));

isPalindrome(palindrome);
isPalindrome(palindrome2);
isPalindrome(palindrome3);

printf("StrnCpy is: %s\n",StrnCpy(buffer,bul,13));
printf("StrCpy: %s\n",StrCpy(buffer,array2copy));



printf("StrCaseCmp of %s and %s is %d\n",tt,tt1,StrCaseCmp(tt,tt1));
printf("Strchar,will print from first occurance of %c in %s (if found), thus: %s\n",test,tt1,StrChr(tt1,test));

ptr_ch= StrDup(mlc_ar);
printf("strdup worked?yay!=> %s\n",ptr_ch);
free(ptr_ch);
ptr_ch=NULL;


printf("StrnCat: %s\n",StrnCat(buffer,bul,10));

printf("StrCat: %s\n",StrCat(buffer,mlc_ar));



free(buffer);
buffer =NULL;
return 0;
}

