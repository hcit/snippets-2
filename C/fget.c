#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char** argv)
{
	char text[100];
	char substring[40];
	int i = 0;   //For Loops

	printf("\nEnter the string to be search:\n");
	fgets(text,sizeof(text),stdin);

	printf("\nEnter the string sought:\n");
	fgets(substring,sizeof(text),stdin);

	/* Overwrites the newline character in each string */
	text[strlen(text)-1] = '\0';
	substring[strlen(substring)-1] = '\0';

	printf("\nThe first string entered:\n%s\n",text);
	printf("\nThe second string entered:\n%s\n",substring);

	for(i = 0;( text[i] = toupper(text[i])); i++);
	for(i = 0;( substring[i] = toupper(substring[i]));i++);

	printf("\nThe second string %s found in the first.\n",
			(strstr(text,substring) == NULL) ? "was not" : "was");
	return 0;
}

