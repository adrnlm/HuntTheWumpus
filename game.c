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
	char userPlayInput[MAXIMUM_PLAY_PARAMETERS];
	Player newPlayer;
	Position playerCurrentPosition;
	Position playerNextPosition;
	int quit=FALSE;
	displayGameMenu();
	getInput("Press enter to continue...", enterButton, sizeof(enterButton));

	/*LOAD OPTION*/
	while (quit==FALSE) {
		char *firstChar;
		char *secondChar;
		getInput("At this stage of the program, only two commands are acceptable:\n"
		"load <g>\n"
		"quit\n\n"
		"Please enter your choice: ", userLoadInput, sizeof(userLoadInput));
		 firstChar = strtok(userLoadInput, " ");
		if ( firstChar != NULL ){
			if ( strcmp(firstChar, COMMAND_QUIT) == 0) {
				quit = TRUE;
				break;
			}
			else {
				secondChar = strtok(NULL, " ");
				if ( secondChar != NULL ) {
					int boardChoice = atoi(secondChar);
					if ( strcmp(firstChar, COMMAND_LOAD)==0 &&
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

	/*INIT OPTION*/
	while (quit==FALSE) {
		char *firstChar;
		char *secondChar;
		getInput("At this stage of the program, only two commands are acceptable:\n"
		"init <x>,<y>\n"
		"quit\n\n"
		"Please enter your choice: ", userInitInput, sizeof(userInitInput));

		 firstChar = strtok(userInitInput, " ");
		if ( firstChar != NULL ) {
			if ( strcmp(firstChar, COMMAND_QUIT) == 0) {
				quit = TRUE;
				break;
			}
			else {
				secondChar = strtok(NULL, ",");
				if ( secondChar != NULL ) {
					char *thirdChar = strtok(NULL, ",");
					if ( thirdChar != NULL ) {
						int positionX = atoi(secondChar);
						int positionY = atoi(thirdChar);
						if ( strcmp(firstChar, COMMAND_INIT)==0 &&
							 ((positionX<=4 && positionX>=1) &&
						 	 (positionY<=4 && positionY>=1))) {
								 playerCurrentPosition.x=positionX;
								 playerCurrentPosition.y=positionY;
								 if ( board_PlacePlayer(currentBoard,playerCurrentPosition)==TRUE) {
							 		player_Initialise(&newPlayer, playerCurrentPosition);
							 		printf("Player Initialized\n");
							 		break;
							 	}
							 	else {
							 		printf("Invalid Space\n\n" );
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

	/*PLAY OPTIONS*/
	while (quit==FALSE) {
		char *firstChar;
		board_Display(currentBoard);
		board_DisplayWarnings(currentBoard, playerCurrentPosition);
		getInput("\n\nAt this stage of the program, only three commands are acceptable:\n"
		"<directions>\n"
		"shoot <directions>\n"
		"quit\n"
		"Where <direction> is one of: north,n,south,s,east,e,west,w\n\n"
		"Please enter your choice: ", userPlayInput, sizeof(userPlayInput));

		firstChar = strtok(userPlayInput, " ");
		if ( firstChar != NULL ) {
			if ( strcmp(firstChar, COMMAND_QUIT) == 0) {
				quit = TRUE;
				break;
			}
			if ( strcmp(firstChar, COMMAND_NORTH) == 0 || strcmp(firstChar, COMMAND_NORTH_SHORTCUT) == 0 ) {
				printf("MOVE %s\n", firstChar);
				/*MOVE NORTH FUNCTION*/
				if ( board_MovePlayer(currentBoard, playerCurrentPosition, player_GetNextPosition(playerCurrentPosition, player_NORTH) ) == board_PLAYER_MOVED ) {
					playerCurrentPosition=playerNextPosition;
					player_UpdatePosition(&newPlayer, playerCurrentPosition);
					printf("MOVED %s\n", firstChar);
					continue;
				}
				else
				 printf("DID NOT MOVE %s\n", firstChar);
				 continue;

			}
			else if ( strcmp(firstChar, COMMAND_SOUTH) == 0 || strcmp(firstChar, COMMAND_SOUTH_SHORTCUT) == 0 ) {
				printf("MOVE %s\n", firstChar);
				/*MOVE SOUTH FUNCTION*/
			}
			else if ( strcmp(firstChar, COMMAND_EAST) == 0 || strcmp(firstChar, COMMAND_EAST_SHORTCUT) == 0 ) {
				printf("MOVE %s\n", firstChar);
				/*MOVE EAST FUNCTION*/
			}
			else if ( strcmp(firstChar, COMMAND_WEST) == 0 || strcmp(firstChar, COMMAND_WEST_SHORTCUT) == 0 ) {
				printf("MOVE %s\n", firstChar);
				/*MOVE WEST FUNCTION*/
			}
			else {
				char *secondChar = strtok(NULL, " ");
				if ( strcmp(firstChar, COMMAND_SHOOT) == 0 && secondChar != NULL ) {
					if ( strcmp(secondChar, COMMAND_NORTH) == 0 || strcmp(secondChar, COMMAND_NORTH_SHORTCUT) == 0 ) {
						printf("SHOOT %s\n", secondChar);
						/*SHOOT NORTH FUNCTION*/
					}
					else if ( strcmp(secondChar, COMMAND_SOUTH) == 0 || strcmp(secondChar, COMMAND_SOUTH_SHORTCUT) == 0 ) {
						printf("SHOOT %s\n", secondChar);
						/*SHOOT SOUTH FUNCTION*/
					}
					else if ( strcmp(secondChar, COMMAND_EAST) == 0 || strcmp(secondChar, COMMAND_EAST_SHORTCUT) == 0 ) {
						printf("SHOOT %s\n", secondChar);
						/*SHOOT EAST FUNCTION*/
					}
					else if ( strcmp(secondChar, COMMAND_WEST) == 0 || strcmp(secondChar, COMMAND_WEST_SHORTCUT) == 0 ) {
						printf("SHOOT %s\n", secondChar);
						/*SHOOT WEST FUNCTION*/
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
	srand(0);
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

void displayGameMenu() {
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
}
