/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim
 * Student number: s3710625
 */
#include "game.h"

void game_PlayGame(){
	Board currentBoard;
	char enterButton[USER_MAX_INPUT];
	char userLoadInput[MAXIMUM_LOAD_PARAMETERS];
	char userInitInput[MAXIMUM_INIT_PARAMETERS];
	Position playerPosition;
	int quit=FALSE;
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
	getInput("Press enter to continue...", enterButton, sizeof(enterButton));

	/*The load option*/
	while (quit==FALSE) {
		getInput("At this stage of the program, only two commands are acceptable:\n"
		"load <g>\n"
		"quit\n", userLoadInput, sizeof(userLoadInput));
		char *firstChar = strtok(userLoadInput, " ");
		if ( firstChar != NULL ){
			if ( strncmp(firstChar, "quit", sizeof(userLoadInput)) == 0) {
				quit = TRUE;
				break;
			}
			else {
				char *secondChar = strtok(NULL, " ");
				if ( secondChar != NULL ) {
					int boardChoice = atoi(secondChar);
					if ( strncmp(firstChar, "load", sizeof(userLoadInput))==0 &&
								(boardChoice==1 || boardChoice==2)) {
									OptionLoadBoard(currentBoard, boardChoice);
									break;
								}
					else {
						printInvalidInput();
						continue;
					}
				}
				else {
					printInvalidInput();
					continue;
				}
			}
		}
		else {
			printInvalidInput();
			continue;
		}
	}

	/*The initialize option*/
	while (quit==FALSE) {
		getInput("At this stage of the program, only two commands are acceptable:\n"
		"init <x>,<y>\n"
		"quit\n", userInitInput, sizeof(userInitInput));

		char *firstChar = strtok(userInitInput, " ");
		if ( firstChar != NULL ) {
			if ( strncmp(firstChar, "quit", sizeof(userInitInput)) == 0) {
				quit = TRUE;
				break;
			}
			else {
				char *secondChar = strtok(NULL, ",");
				if ( secondChar != NULL ) {
					char *thirdChar = strtok(NULL, ",");
					if ( thirdChar != NULL ) {
						int positionX = atoi(secondChar);
						int positionY = atoi(thirdChar);
						if ( strncmp(firstChar, "init", sizeof(userInitInput))==0 &&
							 ((positionX<=4 && positionX>=1) &&
						 	 (positionY<=4 && positionY>=1))) {
								 printf("TRUE\n" );
								 playerPosition.x=positionX;
								 playerPosition.y=positionY;
								 printf("%d\n", positionX);
								 printf("%d\n", playerPosition.x);
								 if ( OptionInitializePlayer(currentBoard, playerPosition)
								 == TRUE )
								 	break;
								 else
								 	continue;
							}
						else {
							printInvalidInput();
							continue;
						}
					}
					else {
						printInvalidInput();
						continue;
					}
				}
				else {
					printInvalidInput();
					continue;
				}
			}
		}
		else {
			printInvalidInput();
			continue;
		}
	}

	board_Display(currentBoard);
	board_DisplayWarnings(currentBoard, playerPosition);

	srand(0);
}

Boolean OptionInitializePlayer(Board currentBoard, Position position){
	Player newPlayer;
	player_Initialise(&newPlayer, position);
	if ( board_PlacePlayer(currentBoard,position)==TRUE) {
		printf("Player Initialized\n");
		return TRUE;
	}
	else {
		printf("Invalid Space\n\n" );
		return FALSE;
	}

  /*printf("SUCCESS\n");*/
}

void OptionLoadBoard(Board board, int userLoadChoice) {
    if ( userLoadChoice == 1 ){
      board_Load(board, BOARD_1);
      printf("Board 1 successfully loaded\n\n");
    }
    else {
      board_Load(board, BOARD_2);
      printf("Board 2 successfully loaded\n\n");
    }

}
