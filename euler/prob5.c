#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
	clock_t start_t,end_t;
	start_t = clock();

	int start = atoi(argv[1]);
	int end   = atoi(argv[2]);

	int i;
	long tmp;


	for(tmp = 2 * end;;tmp += end)
		for(i = start; i <= end; i++)
			if((tmp % i) != 0)
				break;
			else if( i == end)
			{
				end_t = clock();
				printf("Ans --> %ld Elapsed --> %.3lf\n",
						tmp,
						((double)(end_t - start_t))/CLOCKS_PER_SEC);
				return 0;
			}
			
}






