#include <stdio.h>

int main(void)
{
	char array[3][3] = {
						{'1','2','3'},
						{'4','5','6'},
						{'7','8','9'}
						};

	int i;

	for(i=0; i < 9; i++)
		printf("--->%3c:\n",*(*array+i));

	return 0;
}


