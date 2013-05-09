#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
	int x = 1;
	int y = 2;
	int sum = 0;
	while(y<atoi(argv[argc-1]))
	{
		if(!(y%2))
			sum += y;
		y = x + y;
		x = y - x;
	}
	printf("%d\n",sum);
	return 0;
}
	
			
