#include <stdio.h>
void drawBoard();
char board[3][3] = { {'1','2','3'},
		     {'4','5','6'},
		     {'7','8','9'}
			        };
int main(int argc, char** argv)
{
	int player = 0;
	int winner = 0;
	int choice = 0;

	int i = 0;
	for(; i<9 && winner == 0; i++)
	{	drawBoard();
		player = i%2 + 1; /* Select player */
		do
		{
			printf("\nPlayer %d, please enter the number of the square"
			       "where you want to place your %c:",player,(player==1)?'X':'O');
			scanf("%d",&choice);
			choice--;
		}while( choice<0 || choice>=9 );

		*(*board + choice) = (player == 1) ? 'X' : 'O';	
		int line = 0;
		for(;line < 3;line++)
			if( ((*(*board + line * 3) == *(*board + line * 3 + 1)) && (*(*board + line * 3) == *(*board + line * 3 + 2))) ||
			    ((*(*board + line )    == *(*board + line + 3))     && (*(*board + line )    == *(*board + line + 6 ))))
				winner = player;
		if(( (*(*board + 2) == *(*board + 4 )) && (*(*board + 2) == *(*board + 6))) ||
		   ( (**board       == *(*board + 4 )) && (**board       == *(*board + 8))))
			winner = player;
	}
	drawBoard();
	if(winner  == 0)
		printf("\nHow boring, it was a draw\n");
	else
		printf("\nCongratulations Player %d, you are the winner!\n",player);
	return 0;
}
void drawBoard()
{
	int i = 0;
	/* Display the board */
	printf("\n\n");
	for(; i<9 ; i++)
		printf(" %c %s",*(*board+i),!((i+1)%3) ? "\n---+---+---\n":"|");

}



