#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int char_int (char i);

int main (int argc, char *argv[])
{
  long n;
  char nstr[100];  
  long digits;

  /* Caculate number of digits */
  for(n = 1, digits= 1; digits <= 1000000;n++) {
	sprintf(nstr, "%ld", n);
	digits += strlen(nstr);
  }
  
  char number[digits];
  
  /* Fill the number */
  for(n = 1, digits=1; digits <= 1000000; n++) {
	sprintf(number+digits, "%ld", n);
	sprintf(nstr, "%ld", n);
	digits += strlen(nstr);
  }
  
  int ans = 1;
  ans *= char_int(number[1]);
  printf("%c %d\n", number[1], char_int(number[1])); 
  ans *= char_int(number[10]);
  printf("%d %d %d\n", ans, number[10], char_int(number[10]));
  ans *= char_int(number[100]);
  printf("%d %d %d\n", ans, number[100], char_int(number[100]));
  ans *= char_int(number[1000]);
  printf("%d %d %d\n", ans, number[1000], char_int(number[1000]));
  ans *= char_int(number[10000]);
  printf("%d %d %d\n", ans, number[10000], char_int(number[10000]));
  ans *= char_int(number[100000]);
  printf("%d %d %d\n", ans, number[100000], char_int(number[100000]));
  ans *= char_int(number[1000000]);
  printf("%d %d %d\n", ans, number[1000000], char_int(number[1000000]));
  
  printf("ans = %d\n", ans);
  printf("\n");
  return 0;
}
	
int char_int (char i)
{
  if(isdigit(i))
	return i - 48;
  else
	return -1;
}
