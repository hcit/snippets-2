#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t BUFFLEN = 128;
const size_t NUMP    = 100;

int main(int argc, char** argv)
{
	char buffer[BUFFLEN];
	char *pBuffer = buffer;
	char *pStr[NUMP];

	int i = 0;
	
	printf("\nYou can enter up to %u messages, each up to %u characters.\n",
			NUMP,BUFFLEN-1);
	for(; i < NUMP; i++)
	{
		pBuffer = buffer;
		printf("\nEnter %s message, or press Enter to end\n",
				i > 0 ? "another": "a");

		while((pBuffer - buffer < BUFFLEN - 1) &&
				((*pBuffer++ == getchar()) != '\n'));

		if((pBuffer - buffer) < 2)
			break;

		if((pBuffer - buffer) == BUFFLEN && *(pBuffer - 1) != '\n')
		{
			printf("String too long");
			i--;
			continue;
		}
		*(pBuffer - 1) = '\0';

		pStr[i] = (char*)malloc(pBuffer-buffer);
		if(pStr[i] = NULL)
		{
			printf("\nOut of memory.\n");
			return 1;
		}

		strcpy(pStr[i],buffer);
	}

	printf("\nIn reverse order, the strins you entered are:\n");

	while(--i >= 0)
	{
		printf("\n%s",pStr[i]);
		free(pStr[i]);
		pStr[i] = NULL;
	}
	return 0;
}
