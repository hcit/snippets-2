#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
	unsigned long *primes = NULL;
	size_t total =     0;
	size_t count =     0;
	size_t i     =	   0;

	printf("How may numbers you would like to display? ");
	scanf("%u",&total);

	total   = total < 4U ? 4U:total;


	primes = (unsigned long *)malloc(total*sizeof(unsigned long));

	if(primes == NULL)
	{
		printf("Not enought Memory! Perhaps you are using Vista.\n");
		return 1;
	}

	*primes 	= 1UL;
	*(primes + 1)   = 2UL;
	count 		= 2U;

	while(count<total)
		*(primes+count) = *(primes+count-1) + *(primes+(count++)-2);

	for(i = 0;i < total; i++)
	{
		if(!(i%5U))
			printf("\n");
		printf("%12lu", *(primes+i));
	}
	printf("\n");
	return 0;
}




