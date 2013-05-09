#include <stdio.h>
#include <stdlib.h>

int main(int argc,char** argv)
{
	int sum = 0;
	int num = 0;
	while(num < atoi(argv[argc-1])){
		if( !(num % 3) || !(num%5))
			sum += num;
		num += 1;
	}
	printf("%d\n",sum);
	return 0;

}
	
