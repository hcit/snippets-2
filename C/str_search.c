#include <stdio.h>
#include <string.h>

int main(void)
{
    char search[10];
    char str[30];
    printf("Enter the string to search:\t");
    scanf("%29s",str);
    printf("\nEnter the word to search:\t");
    scanf("%9s",search);

    if( strstr(str,search) != NULL)
        printf("%s was found at position",search);
    else
        printf("%s was not found",search);

}

