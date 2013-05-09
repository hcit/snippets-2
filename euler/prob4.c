#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFSIZ 128

bool isPalindrome(char*);

int main(int argc,char** argv)
{
	int m,n;
	char buff[BUFFSIZ];
	long lp = 0; //largest palindrome
	for( m = 999; m > 99 ;m--)
	{
		for(n = 999; n > 99; n --)
		{
			sprintf(buff,"%d",(m*n));
			if(isPalindrome(buff))
				if(atol(buff) > lp)
					lp = atol(buff);
			
		}
	}
	printf("Largest Palindrome = %ld\n",lp);
	return 0;
}

bool isPalindrome(char* str)
{
	int len = strlen(str);
	int i;
	for(i = 0; i <= len/2;i++)
	{
		if( *(str+i) == *(str+len-i-1))
			continue;
		else
			return false;
	}
	return true;
}


