#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFLEN 100
#define NUMP 	100

int main(int argc, char** argv)
{
	char buffer[BUFFLEN];
	char *pS[NUMP] = {NULL};
	char *pTemp    = NULL;

	int i = 0;
	bool sorted = false;
	int last_string = 0;

	printf("\nEnter the lines, press Enter to end.\n");
	while((*fgets(buffer,BUFFLEN,stdin) != '\n') && i < NUMP)
	{
		pS[i] = (char*)malloc(strlen(buffer) +1);
		if(pS[i] = NULL)
		{
			printf("Memory Allocation failed. Program terminated.\n");
			return 1;
		}
		strcpy(pS[i++],buffer);
	}
	last_string = i;
	while(!sorted)
	{
		sorted = true;
		for(i = 0; i < last_string -1; i++)
			if(strcmp(pS[i],pS[i+1]) > 0)
			{ 
				sorted = false;
				pTemp  = pS[i];
				pS[i]  = pS[i+1];
				pS[i+1]= pTemp;
			}
	}

	printf("\nYour input sorted in order is:\n\n");
	for(i = 0;i < last_string; i++)
	{
		printf("%s\n",pS[i]);
		free(pS[i]);
		pS[i] = NULL;
	}
	return 0;
}




