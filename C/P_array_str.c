#include <stdio.h>
#include <stdlib.h>

const size_t BUFFLEN = 512;

int main(int argc,char** argv)
{
	char buffer[BUFFLEN];
	char *pStr[3] = {NULL};
	char *pBuffer = buffer;
	size_t index  = 0;

	printf("Enter  3 messages.\n");

	int i;
	for(i = 0;i < 3; i++)
	{
		printf("\nEnter %s message\n", i>0 ? "another":"a");
		pStr[i] = &buffer[index];
		for(; index < BUFFLEN; index++)
			if((*(pBuffer+index) = getchar()) == '\n')
			{
				*(pBuffer+index++) = '\0';
				break;
			}
		if((index == BUFFLEN) && ((*(pBuffer+index-1) != '\0') || (i<2)))
		{
			printf("\nYou ran out of space in the buffer.");
			return 1;
		}
	}

	printf("\nThe strings you entered are:\n\n");
	for(i = 0; i <3; i++)
		printf("%s\n",pStr[i]);

	printf("The buffer had %d characters unused.\n",
			BUFFLEN-index);
	return 0;
}

