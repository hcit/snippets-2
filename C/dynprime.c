/*	Program 7.11 A Dynamic prime example	*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main (int argc,char** argv)
{
	unsigned long *primes = NULL; 	/* Pointer to prime storage aread	  */
	unsigned long tmp = 0;    	/* Integer to be tested 		  */
	bool found = false;		/* Indicates whether we found a integer   */
	size_t total = 0;	 	/* Total Numbers of primes to be found    */
	size_t count = 0;		/* Total Numbers of primes that have been found */

	printf("How many primes whould you like? ");
	scanf("%u", &total);
	total = total < 4U ? 4U:total; 	/* Checks whether the total is less than 4 */

	/*  Allocates sufficient memory to store the number of primes required 	   */
	primes = (unsigned long *)malloc(total*sizeof(unsigned long));
	if(primes == NULL)
	{
		printf("Not Enough Memory, Hasta la Vista Baby");
		return 1;
	}

	/* Start with the first three primes 	*/
	*primes 	= 2UL;
	*(primes + 1) 	= 3UL;
	*(primes + 2) 	= 5UL;
	count 	=3UL;
	tmp 	=5UL;

	/*  Find all the primes required 	*/
	while(count<total)
	{
		tmp += 2UL; 		/* Set next number to be checked */

		/* Try dividing each of the primes we have */
		/* If any, the number is not prime	   */
		size_t i = 0;
		for(; i < count; i++)
			if(!(found = (tmp % *(primes+i))))
				break;
		if(found)
			*(primes+count++) = tmp; /* If found is true, then store it and increase count */
	}

	/* 	Displaying 	*/
	size_t i =0;
	for(; i < total; i++)
	{
		if(!(i%5U))
			printf("\n");
		printf("%12lu",*(primes+i));
	}
	printf("\n");
	return 0;
}
			
			
	

	

	
