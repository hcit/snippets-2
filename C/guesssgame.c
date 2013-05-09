#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv)
{
	int chosen = 0;
	int guess   = 0;
	int count   = 5;
	int limit   = 20;

	srand(time(NULL));
	chosen = 1 + rand()%limit;

	for(; count> 0; count--)
	{
		printf("\nYou have %d tr%s left.",count,count==1? "y":"ies");
		printf("\nEnter a guess: ");
		scanf("%d",&guess);

		if(guess == chosen)
		{
			printf("You guess it with %d times!\n",5-(--count));
			return 0;
		}

		if(guess<1 || guess > 20)
			printf("The number should be between 1 and 20");
		else
			printf("Sorry.%d is wrong. The number is %s than %d",guess, guess<chosen ? "greater":"less",guess);
	}
	printf("\nTime's up. The chosen one was %d\n",chosen);
	return 0;
}
