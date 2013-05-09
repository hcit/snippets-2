#include <stdio.h>
#include <string.h>

static int my_strstr (const char * haystack, const char * needle)
{
  int m, n = 0;
  
  while (strlen(needle) < strlen (haystack+n)) {

    printf ("haystack ==> %s\n", haystack+n);
    m = 0;
    
    while (needle[m] == haystack [m+n]) {
      if ( m == strlen (needle) - 1) {
	return n;
      }
      m++;
    }
    n++;
  }
  return -1;
}


int main( int argc, char* argv[] ) {
  printf("%d\n", my_strstr ("", "isla"));
  printf("%d\n", my_strstr ("life is a game.", ""));
  printf("%d\n", my_strstr ("life is a game.", "isl"));
  printf("%d\n", my_strstr ("life is a game.", "is"));
  return 0;
}
