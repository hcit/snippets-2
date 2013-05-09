#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	char block[1024];
	int in,out;
	
	in  = open("/home/thura/Desktop/padonma-english-myanmar.bgl",O_RDONLY);
	out = open("/home/thura/Desktop/buff",O_WRONLY, S_IRUSR | S_IWUSR);
	while(read(in,block,sizeof(block)) == 1)
		write(out,block,1);
	
	exit(0);
}
