#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define CAPACITY 1000000

int main(int argc,char** argv)
{
	long chaincount;
	long i;
	long long m;
	clock_t start_t;
	long cgnum = 1; //current number with greatest chaincount
        long cgc = 1;	//current greatest chaincount number
	bool checked[CAPACITY] = {false};
	
	start_t = clock();
	for(i = 1; i < CAPACITY; i++)
	{
		m = i;
		chaincount = 0;
		if(!checked[m])
		{	while(m != 1)
			{  	
				if(!(m%2))
					m = m / 2;
				else
					m = (3 * m ) + 1;
				if(m < CAPACITY)
					checked[m] = true;
				chaincount++;
				
			}
		}
		if(++chaincount > cgc) //increment as 1 haven't included yet 
		{
			cgc   = chaincount;
			cgnum = i;
		}
	}
	printf("%ld with %ld chaincount\nElapsed Time : %f\n",
			cgnum,cgc,
			(double)((clock() - start_t)/CLOCKS_PER_SEC));
	return 0;
}





