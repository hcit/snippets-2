#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int count(char*);
int  *counts = {NULL};

int main(int* argc,char** argv)
{	int i;
	char *tmp = "This is a fucknig string,\nthat does noth ...";
	printf("%s\ncount= %d",tmp,count(tmp));
}

int count(char* str)
{	int total =0;
	int tmp;
	while( getc(str) != '\n')
			total++;
	return total;
}



