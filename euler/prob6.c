#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv)
{	
	int range = atoi(argv[1]);
	int i;
	long sum1 = 0;
	long sum2 = 0;

	for(i = 1; i <= range; i++)
	{ 
		sum1 += i*i;
		sum2 += i;
	}
	sum2 *= sum2;
	printf("Ans--> %ld\n",sum2-sum1);
	return 0;
}



