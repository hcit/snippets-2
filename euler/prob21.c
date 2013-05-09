#include <stdio.h>
#include <stdlib.h>


struct number {
  int value;
  int sopd;
};

/* Sum of Proper Divisors */
int sopd (int val) {
  int i, sum = 0;
  for(i = 1; i < val; i++)
	if(!(val % i)) {
	  sum += i;
	}
  return sum;
}

int main(int argc, char *argv[])
{
  struct number numbers[10000];
  
  int i, d;
  long sum = 0;
  
  for(i = 1; i < 10000; i++)
  	numbers[i].sopd = sopd(i);

  for(i = 1; i < 10000; i++) {
  	d = numbers[i].sopd;
  	if(d < 10000 && d > i)
  	  if(i == numbers[d].sopd)
		sum += (i+d);

  }
  printf("sum = %ld\n", sum);
  return 0;
}
