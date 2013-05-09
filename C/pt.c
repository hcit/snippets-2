#include <stdio.h>

int main(void)
{
    long num1  = 0L;
    long num2  = 0L;
    long *pnum =NULL;

    pnum    = &num1;
    *pnum	= 2;

    ++num2;
    num2 += *pnum;

    pnum = &num2;
    ++*pnum;

    printf("\num1= %1d num2 = %1d *pnum = %1d ",num1,num2,*pnum);

    int value   = 0;
    int *pvalue = NULL;

    pvalue = &value;

    printf("Input an integer: ");
    scanf("%d", pvalue);

    printf("\nYou entered %d\n",*pvalue);
    return 0;

}



