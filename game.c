/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim
 * Student number: s3710625
 */
#include "game.h"

void game_PlayGame(){
	Board currentBoard;
	char userGameInput[USER_MAX_INPUT];
	Position playerPosition;
	printf("\n\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("You can use the following commands to play the game:\n\n");
	printf("load <g>\n");
	printf(" g:number of the game board to load (either 1 or 2)\n");
	printf("init <x>,<y>\n");
	printf(" x:horizontal position of the player on the board (between 0 & 4)\n");
	printf(" y:vertical position of the player on the board (between 0 & 4)\n");
	printf("north (or n)\n");
	printf("south (or s)\n");
	printf("east (or e)\n");
	printf("west (or w)\n");
	printf("quit\n\n");

	char * userPromt = "Enter a command:";
	int quit = 1;
	do {
		quit=0;
		getInput(userPromt, userGameInput, USER_MAX_INPUT);
		char *firstChar = strtok(userGameInput, "., ");
		char *secondChar = strtok(NULL, "., ");
		char *thirdChar = strtok(NULL, "., ");

		if ( strncmp(userGameInput, "load", MAXIMUM_CHAR_PARAMETERS)==0) {
			int userBoardChoice = atoi(secondChar);
			OptionLoadBoard(currentBoard, userBoardChoice);
		}
		else if ( strncmp(userGameInput, "init", MAXIMUM_CHAR_PARAMETERS)==0 ) {
			OptionInitializePlayer(currentBoard, playerPosition);
		}
		else if ( strncmp(userGameInput, "quit", MAXIMUM_CHAR_PARAMETERS)==0 ) {
			break;
		}



} while(quit==0);

board_Display(currentBoard);
board_DisplayWarnings(currentBoard, playerPosition);

	srand(0);
}

void OptionInitializePlayer(Board currentBoard, Position *position){
  int coordinatesVerifier=0;
  Player newPlayer;
  printf("\nInitialize player position\n" );
  printf("- - - - - - - - - - - - - - - - -\n");
  do {
    printf("Enter coordinates X: " );
    scanf("%d", &position->x);
    if (position->x>=0 && position->x<=4) {
      printf("Enter coordinates Y: " );
      scanf("%d", &position->y);
      if (position->y>=0 && position->y<=4) {
        player_Initialise(&newPlayer, *position);
				if ( board_PlacePlayer(currentBoard,*position)==TRUE) {
					printf("Player Initialized\n");
					printf(" init %d\n", position->x );
					coordinatesVerifier=1;
				}
				else {
					printf("Invalid space\n" );
        	coordinatesVerifier=0;
				}
      }
      else {
        printf("Invalid coordinates. Enter number between 0-4\n\n" );
        coordinatesVerifier=0;
      }
    }
    else {
      printf("Invalid coordinates. Enter number between 0-4\n\n" );
      coordinatesVerifier=0;
    }
  } while(coordinatesVerifier==0);

  /*printf("SUCCESS\n");*/
}

void OptionLoadBoard(Board board, int userLoadChoice) {
    if ( userLoadChoice == 1 ){
      board_Load(board, BOARD_1);
      printf("Board 1 successfully loaded\n\n");
    }
    else if (  userLoadChoice == 2 ){
      board_Load(board, BOARD_2);
      printf("Board 2 successfully loaded\n\n");
    }
		else {
			printf("Invalid Board: Pick 1 or 2\n\n");
		}

}
