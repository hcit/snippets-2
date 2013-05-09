#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(int argc,char** argv)
{
	long number = 13195;
	int m,n;
	for(m = 2; m < number/2;m++)
		if(!(number%m))
			for(n = 2;n < sqrt(number/m);n++)
				if(!((number/m)%n))
					break;
				else if( n == sqrt(number/m)-1){
					printf("The largest prime factor for %ld"
							" is %ld.\n",number,number/m);
					exit(0);
				}
	return 0;
}
