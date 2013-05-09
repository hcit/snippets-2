#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	long sum = 0;
	int factors;
	int m,n;
	int over = atoi(argv[1]);
	clock_t start = clock();
	
	for(m = 1;;m++)
	{
		sum += m;
		factors = 0;
		
		for(n = 1; n <= sum/2;n++)
			if(!(sum%n))
				factors++;

		if( factors >= over)
			break;
		printf("%5d.  %10ld with %d factors.\n",m,sum,factors);
	}

	printf("#############################################\n"
	       "               Elapsed Time = %f             \n"
	       "#############################################\n"				, (double) ((clock() -start)/CLOCKS_PER_SEC));
	

	printf("The triangle number with %d factors is %ld.\n",over,sum);
	return 0;
}






