#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv)
{
	char another_game = 'Y';
	bool correct = true;

	int counter = 0;
	int sequence_length = 0;
	time_t seed = 0;
	int number  = 0;
	time_t now  = 0;
	int time_taken = 0;

	/*Description for the game */
	printf("\nTo play Simple Simon,");
	printf("watch the screen for a sequence of digits.");
	printf("\nWatch carefully, as the digits are only displayed"
			"for a second!");
	printf("\nThe computer will remove them, and them prompt you");
	printf("to enter the same sequence.");
	printf("\nGood Luck!\nPress Enter to play");
	scanf("%c",&another_game);

	/* loop for a game*/
	do
	{
		correct = true;
		counter = 0;
		sequence_length = 2;
		time_taken  = clock();
		while(correct)
		{			
			/* On every third successful try, increase the sequence length */
			sequence_length += counter++%3 == 0;
			seed  = time(NULL);		/*Set the seed */
			srand((unsigned int)seed);	/*Initialize   */
			now = clock();			/*record start time */
			int i = 1;			/* To use in Loops  */
			for(;i <= sequence_length; i++)
				printf("%d", rand() % 10);
			for(;clock()-now;CLOCKS_PER_SEC);/* Wait one second */
			/* Now overwrite the digit sequence 	*/
			printf("\r"); 		/* Go to the beginning of the line */
			for(i =1; i <= sequence_length; i++)
				printf(	" ");			
			/* Prompt for the input sequence 	*/
			if(counter == 1)
				printf("\nNow you enter the  sequence - don't forget"
						" the spaces\n");
			else
				printf("\r");
			srand((unsigned int)seed); /*Restart the random sequence */
			for(i = 1; i < sequence_length; i++)
			{
				scanf("%d",&number);
				if(number != rand() % 10)
				{
					correct = false;
					break;
				}
			}
			printf("%s\n", correct ? "Correct!":"Wrong!");
		}
		time_taken = (clock() - time_taken)/ CLOCKS_PER_SEC;
		printf("\n\nYour score is %d",--counter * 100 / (int)time_taken);
		fflush(stdin);

		printf("\nDo you want to play again (y|n)?)");
		scanf("%c",&another_game);
	}while(toupper(another_game)  == 'Y');
	return 0;
}

