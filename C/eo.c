#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
	int num;
	num = atoi(argv[1]);
	printf("%d",num);
	isEven(num);
	isOdd(num);
}

void isEven(int num)
{
	if(num == 0)
		printf("\nTrue");
	else
		isOdd(num-1);
}
void isOdd(int num)
{
	if(num == 0)
		printf("\nFalse");
	else
		isEven(num-1);
}
