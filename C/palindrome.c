#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE    100
int main(int argc, char *argv[])
{
    printf("Enter the string: ");

    char *word = (char*)malloc(SIZE);
    char *pword = word;

    while((*pword++ = getchar()) !='\n');
    *pword--;
    *pword-- = '\0';

    int len = strlen(word);
    int i = 1;
    while( i <= len/2) {
        if((char)*word++ != (char)*pword--) {
            puts("That is not a palindrome");
            break;
        }
        else if( i == len/2 )
            puts("That's a palindrome");
        i++;
    }

    return 0;
}