#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFLEN  256

int main(int argc,char** argv)
{
	char input[BUFFLEN];
	char num_str[30];
	unsigned int index = 0;
	unsigned int to    = 0;
	size_t input_len   = 0;
	unsigned int num_len = 0;
	double result = 0.0;
	char op = 0;
	double number = 0.0;

	while(strcmp(fgets(input,BUFFLEN,stdin),"quit\n") != 0)
	{
		input_len = strlen(input);
		input[--input_len] = '\0';
		
		for(to = 0, index = 0; index <= input_len; index++)
			if(*(input+index) != ' ')
				*(input+to++) = *(input+index);
		input_len = strlen(input);
		index = 0;

		if(input[index] == '=')
			index++;
		else
		{
			num_len = 0;
			if(input[index] == '+' || input[index] == '-')
				*(num_str+num_len++) = *(input+index++);

			for(;isdigit(*(input+index));index++)
				*(num_str+num_len++) = *(input+index);
			
			if(*(input+index) == '.')
			{
				*(num_str+num_len++) = *(input+index++);

				for(;isdigit(*(input+index));index++)
					*(num_str+num_len) = *(input+index);
			}
			*(num_str+num_len) = '\0';

			if(num_len > 0)
				result = atof(num_str);
		}



	}

	return 0;
}

