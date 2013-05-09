#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	char str[10];
	printf("Enter a string less than 10 chars:");
	scanf("%s",str);

	if((write(1,str,10)) != 10)
		write(2,"The str got more than 10 chars",30);

	return 0;
}
