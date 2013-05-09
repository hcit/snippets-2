#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZ 6965

int main(int argc,char** argv)
{
	int abundant_num[SIZ];
	int abundant_count = 0;
	
	long i,m,n;
	int sum_of_factors;
	long long sum = 0;

	bool checked[28124] = {false};
	
	for(i = 1; i <= 28123; i++)
	{		
	//	if(checked[i])
	//	{	abundant_num[abundant_count] = i;
	//		abundant_count++;
	//		continue;
	//	}
		sum_of_factors = 0;

		for(m = 1; m <= i / 2; m++)
			if(!(i%m))
				sum_of_factors += m;

		if(sum_of_factors > i)
		{	abundant_num[abundant_count] = i;
			abundant_count++;
		//	for(n = i*2; n <= 28123; n *= 2)
		//		checked[n] = true;
		}
		
	}
	printf("%d\n",abundant_count);
	for( i = 0; i < 6965; i++)
		for( m = i; m < 6965; m++)
		{	
			if( (n = abundant_num[i] + abundant_num[m]) > 28123)
				break;
			else
			{	
				checked[n] = true;
			}
		}

	for( i = 1; i <= 28123; i++)
		if(!checked[i])
			sum += i;
	
	printf("\n%lld",sum);	

	return 0;
}






