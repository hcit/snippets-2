#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if (argc < 4)
	exit(1);

  long long number = atol(argv[1]);  
  long long upper_bound = atol(argv[3]);
  char od[150];
  char nd[150];
  int i, m, n = atoi(argv[2]);
  char *bool;

  while (number < upper_bound) {
	
	sprintf(od, "%lld", number);

	for(i = 2; i <= n; i++) {
	  
	  sprintf(nd, "%lld", i * number);
	  
	  for(m = 0; m < strlen(nd);) {
		//		printf(" %s %d %c", nd, m, nd[m]);
		if(!(bool = strchr(od, nd[m])))
		   break;
		/*		else if (++m ==  strlen(nd) && i == n)
				printf("%s %s \n", od, nd); */
		else
		  continue;
	  }	  
	  if ( bool && i == n)  {
		printf("\n%s\n", od);
		return 0;
	  }
	  break;
	}
	number++;
	}

  return 0;
}
