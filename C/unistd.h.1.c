#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	 char buffer[12];
	 int nread;

	 nread = read(0,buffer,12);

	 if ( nread == -1)

		write(2,"An error occured !",sizeof("An error occured !"));

	 if ((write(1,buffer,nread) != nread))
		write(2,"A write error occured!",sizeof("A write error occured!"));

	return 0;
}
