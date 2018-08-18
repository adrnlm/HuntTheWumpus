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

	/*Load option*/
	while (quit==FALSE) {
		getInput("At this stage of the program, only two commands are acceptable:\n"
		"load <g>\n"
<<<<<<< HEAD
		"quit\n\n"
=======
		"quit\n"
>>>>>>> 69122604856890a9db6192bfbbae9bf1e8e474eb
		"Please enter your choice: ", userLoadInput, sizeof(userLoadInput));
		char *firstChar = strtok(userLoadInput, " ");
		if ( firstChar != NULL ){
			if ( strncmp(firstChar, COMMAND_QUIT, sizeof(userLoadInput)) == 0) {
				quit = TRUE;
				break;
			}
			else {
				char *secondChar = strtok(NULL, " ");
				if ( secondChar != NULL ) {
					int boardChoice = atoi(secondChar);
					if ( strncmp(firstChar, COMMAND_LOAD, sizeof(userLoadInput))==0 &&
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

	/*Initialize option*/
	while (quit==FALSE) {
		getInput("At this stage of the program, only two commands are acceptable:\n"
		"init <x>,<y>\n"
<<<<<<< HEAD
		"quit\n\n"
=======
		"quit\n"
>>>>>>> 69122604856890a9db6192bfbbae9bf1e8e474eb
		"Please enter your choice: ", userInitInput, sizeof(userInitInput));

		char *firstChar = strtok(userInitInput, " ");
		if ( firstChar != NULL ) {
			if ( strncmp(firstChar, COMMAND_QUIT, sizeof(userInitInput)) == 0) {
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
						if ( strncmp(firstChar, COMMAND_INIT, sizeof(userInitInput))==0 &&
							 ((positionX<=4 && positionX>=1) &&
						 	 (positionY<=4 && positionY>=1))) {
								 playerPosition.x=positionX;
								 playerPosition.y=positionY;
								 if ( OptionInitializePlayer(currentBoard, newPlayer,
									  playerPosition)
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

	/*Play options*/
<<<<<<< HEAD
	while (quit==FALSE) {
		board_Display(currentBoard);
		board_DisplayWarnings(currentBoard, playerPosition);
		getInput("\n\nAt this stage of the program, only three commands are acceptable:\n"
=======
	while (quit==False) {
		getInput("At this stage of the program, only three commands are acceptable:\n"
>>>>>>> 69122604856890a9db6192bfbbae9bf1e8e474eb
		"<directions>\n"
		"shoot <directions>\n"
		"quit\n"
		"Where <direction> is one of: north,n,south,s,east,e,west,w\n\n"
		"Please enter your choice: ", userPlayInput, sizeof(userPlayInput));

		char *firstChar = strtok(userPlayInput, " ");
		if ( firstChar != NULL ) {
<<<<<<< HEAD
			if ( strncmp(firstChar, COMMAND_QUIT, sizeof(userPlayInput)) == 0) {
				quit = TRUE;
				break;
			}
			if ( strncmp(firstChar, COMMAND_NORTH, sizeof(userPlayInput)) == 0 || strncmp(firstChar, COMMAND_NORTH_SHORTCUT, sizeof(userPlayInput)) == 0 ) {
				printf("MOVE %s\n", firstChar);
				/*MOVEMENT FUNCTION*/
			}
			else if ( strncmp(firstChar, COMMAND_SOUTH, sizeof(userPlayInput)) == 0 || strncmp(firstChar, COMMAND_SOUTH_SHORTCUT, sizeof(userPlayInput)) == 0 ) {
				printf("MOVE %s\n", firstChar);
				/*MOVEMENT FUNCTION*/
			}
			else if ( strncmp(firstChar, COMMAND_EAST, sizeof(userPlayInput)) == 0 || strncmp(firstChar, COMMAND_EAST_SHORTCUT, sizeof(userPlayInput)) == 0 ) {
				printf("MOVE %s\n", firstChar);
				/*MOVEMENT FUNCTION*/
			}
			else if ( strncmp(firstChar, COMMAND_WEST, sizeof(userPlayInput)) == 0 || strncmp(firstChar, COMMAND_WEST_SHORTCUT, sizeof(userPlayInput)) == 0 ) {
				printf("MOVE %s\n", firstChar);
				/*MOVEMENT FUNCTION*/
			}
			else {
				char *secondChar = strtok(NULL, " ");
				if ( strncmp(firstChar, COMMAND_SHOOT, sizeof(userPlayInput)) == 0 && secondChar != NULL ) {
					if ( strncmp(secondChar, COMMAND_NORTH, sizeof(userPlayInput)) == 0 || strncmp(secondChar, COMMAND_NORTH_SHORTCUT, sizeof(userPlayInput)) == 0 ) {
						printf("SHOOT %s\n", secondChar);
						/*SHOOT FUNCTION*/
					}
					else if ( strncmp(secondChar, COMMAND_SOUTH, sizeof(userPlayInput)) == 0 || strncmp(secondChar, COMMAND_SOUTH_SHORTCUT, sizeof(userPlayInput)) == 0 ) {
						printf("SHOOT %s\n", secondChar);
						/*SHOOT FUNCTION*/
					}
					else if ( strncmp(secondChar, COMMAND_EAST, sizeof(userPlayInput)) == 0 || strncmp(secondChar, COMMAND_EAST_SHORTCUT, sizeof(userPlayInput)) == 0 ) {
						printf("SHOOT %s\n", secondChar);
						/*SHOOT FUNCTION*/
					}
					else if ( strncmp(secondChar, COMMAND_WEST, sizeof(userPlayInput)) == 0 || strncmp(secondChar, COMMAND_WEST_SHORTCUT, sizeof(userPlayInput)) == 0 ) {
						printf("SHOOT %s\n", secondChar);
						/*SHOOT FUNCTION*/
					}
					else {
						printInvalidInput();
						continue;
					}
=======
			if ( strncmp(firstChar, COMMAND_QUIT, sizeof(userInitInput)) == 0) {
				quit = TRUE;
				break;
			}
			else if {
				/*MOVEMENT FUNCTION*/
				
			}
			else {
				char *secondChar = strtok(NULL, " ");
				if ( secondChar != NULL ) {
					/*SHOOT FUNCTION*/
>>>>>>> 69122604856890a9db6192bfbbae9bf1e8e474eb
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
<<<<<<< HEAD
=======












	board_Display(currentBoard);
	board_DisplayWarnings(currentBoard, playerPosition);

>>>>>>> 69122604856890a9db6192bfbbae9bf1e8e474eb
	srand(0);
}

Boolean OptionInitializePlayer(Board currentBoard, Player newPlayer,
	Position position){
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
