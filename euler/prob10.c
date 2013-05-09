#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define LIMIT 1000000

int main(int argc,char** argv)
{
	
	bool crossed[LIMIT+1] = {false};
	long n,m;

	crossed[0] = true; 
	crossed[1] = true;

	long long sum = 0;

	for(n = 4; n <=LIMIT; n += 2)
		crossed[n] = true;

	for(n = 3; n<= 1000; n +=2)
		if(!crossed[n])
			for(m = n*n; m <= LIMIT; m += n*2)
				crossed[m] = true;

	for(n =2; n<= LIMIT; n++)
		if(!crossed[n])
			sum += n;
	printf("Sum of primes under %d is %lld.\n",LIMIT,sum);	
	return 0;
}









