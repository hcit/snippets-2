#include <stdio.h>
#include <stdarg.h>

#define dc (double)

double average(double v1, double v2, ...);

int main(void)
{
	double v1 = 10.5, v2 = 2.5;
	int num1  = 6,  num2 =   5;
	long num3 = 12, num4 =  20;

	printf("\nAverage = %1f",  average(v1,3.5,v2,4.5,0.0));
	printf("\nAverage = %1f",  average(1.0,2.0,0.0));
	printf("\nAverage = %1f\n",average(dc num2,v2,dc num1,dc num4,dc num3,0.0));

	return 0;
}

double average(double v1, double v2, ...)
{
	va_list arglist;
	double  sum  = v1 + v2;
	double value = 0;

	int count =  2;

	va_start(arglist,v2);

	while((value = va_arg(arglist, double)) != 0.0)
	{
		sum += value;
		count++;
	}

	va_end(arglist);
	return sum/count;
}

