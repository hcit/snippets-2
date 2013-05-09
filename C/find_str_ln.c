#include <stdio.h>

int main(void)
{   char str[20];
    printf("Enter the string:");
    scanf("%s",str);
    printf("\n%s",str);
    printf("\nThe length of the str is %d",findStrLn(str));
    return 0;

}
int findStrLn(char str[])
{
    int count=0;
    while(str[count] != '\0')   /* You can also just you (str[count]) */
        count++;
    return count;
}

