/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim Song En
 * Student number: s3710625
 */
#include "game.h"

void game_PlayGame(){
	Board currentBoard;
	char enterButton[USER_MAX_INPUT];
	char userQuitInput[MAXIMUM_QUIT_PARAMETERS];
	char userLoadInput[MAXIMUM_LOAD_PARAMETERS];
	char userInitInput[MAXIMUM_INIT_PARAMETERS];
	char userPlayInput[MAXIMUM_PLAY_PARAMETERS];
	Player newPlayer;
	Direction moveDirection,
	 					shootDirection;
	Position playerCurrentPosition,
					 playerNextPosition,
					 playerShootDirection;
	int quit=FALSE;
	displayGameMenu();
	getInput("Press enter to continue...", enterButton, sizeof( enterButton ));

	/*LOAD OPTION*/
	while ( quit==FALSE ) {
		/*	char *firstChar;
		char *secondChar;
		getInput("At this stage of the program, only two commands are"
						 "acceptable:\n"
						 "load <g>\n"
						 "quit\n\n"
						 "Please enter your choice: ",
						 	userLoadInput,
							sizeof( userLoadInput ));

		 firstChar = strtok( userLoadInput, " " );
		if ( firstChar != NULL ){
			if ( strcmp( firstChar, COMMAND_QUIT ) == 0 ) {
				quit = TRUE;
				break;
			}
			else {
				secondChar = strtok(NULL, " ");
				if ( secondChar != NULL ) {
					int boardChoice = atoi( secondChar );
					if ( strcmp( firstChar, COMMAND_LOAD )==0 &&
								( boardChoice==1 || boardChoice==2 )) {
									OptionLoadBoard( currentBoard, boardChoice );
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
		}*/
		if ( loadFunction(currentBoard, userLoadInput) == TRUE )
			break;
			else
	 	continue;
	}

	/*INIT OPTION*/
	while ( quit==FALSE ) {
		char *firstChar;
		char *secondChar;
		getInput( "At this stage of the program, only two commands are acceptable:\n"
							"init <x>,<y>\n"
							"quit\n\n"
							"Please enter your choice: ",
								userInitInput,
								sizeof(userInitInput));

		 firstChar = strtok( userInitInput, " " );
		if ( firstChar != NULL ) {
			if ( strcmp( firstChar, COMMAND_QUIT ) == 0) {
				quit = TRUE;
				break;
			}
			else {
				secondChar = strtok( NULL, "," );
				if ( secondChar != NULL ) {
					char *thirdChar = strtok( NULL, "," );
					if ( thirdChar != NULL ) {
						int positionX = atoi( secondChar );
						int positionY = atoi( thirdChar );
						if ( strcmp(firstChar, COMMAND_INIT )==0 &&
							 	(( positionX<=4 && positionX>=1 ) &&
						 	 	 ( positionY<=4 && positionY>=1 ))) {
								 playerCurrentPosition.x = positionX;
								 playerCurrentPosition.y = positionY;
								 if ( board_PlacePlayer( currentBoard,
									 											 playerCurrentPosition ) ==
																				 	TRUE ) {
							 		player_Initialise( &newPlayer, playerCurrentPosition );
							 		printf( "Player Initialized\n" );
							 		break;
							 	}
							 	else {
							 		printf( "Invalid Space\n\n" );
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
		/*if ( initFunction( currentBoard, userInitInput, &newPlayer ) == TRUE )
			break;
		else
			continue; */
	}

	/*PLAY OPTIONS*/
	while ( quit==FALSE ) {
		char *firstChar;
		board_Display( currentBoard );
		board_DisplayWarnings( currentBoard, playerCurrentPosition );
		getInput("\n\nAt this stage of the program, only three commands are "
							"acceptable:\n"
							"<directions>\n"
							"shoot <directions>\n"
							"quit\n"
							"Where <direction> is one of: north,n,south,s,east,e,west,w\n\n"
							"Please enter your choice: ",
								userPlayInput,
								sizeof( userPlayInput ));

		firstChar = strtok( userPlayInput, " \n" );
		if ( firstChar != NULL ) {
			if ( strncmp( firstChar, COMMAND_QUIT, sizeof( userQuitInput )) == 0 ) {
				quit = TRUE;
				break;
			}
			if ( getDirection( firstChar, &moveDirection )) {
				playerNextPosition = player_GetNextPosition( playerCurrentPosition,
																										 moveDirection );
				if ( board_MovePlayer( currentBoard,
															 playerCurrentPosition,
															 playerNextPosition ) ==
															 	board_PLAYER_MOVED ) {
					printf("Player moved.\n");
					playerCurrentPosition = playerNextPosition;
					player_UpdatePosition( &newPlayer, playerCurrentPosition );
					continue;
				}
				else if ( board_MovePlayer(
										currentBoard,
										playerCurrentPosition,
										playerNextPosition ) ==
											board_BAT_CELL ) {
					/*Random Placement*/
					printf("Bat Cell!\n");
					playerCurrentPosition = batRandom( currentBoard, playerCurrentPosition );
					player_UpdatePosition( &newPlayer, playerCurrentPosition);
					continue;
				}
				else if ( board_MovePlayer( currentBoard,
																		playerCurrentPosition,
																		playerNextPosition ) ==
																			board_OUTSIDE_BOUNDS ) {
					printf("Unable to move - outside bounds.\n");
					continue;
				}
				else  {
					printf("Player killed!\n");
					break;
				}
			}
			else {
				char *secondChar = strtok(NULL, " ");
				if ( strcmp( firstChar, COMMAND_SHOOT ) == 0 &&
							getDirection( secondChar, &shootDirection ) == TRUE ) {
					/*SHOOT FUNCTION*/
					if ( newPlayer.numArrows>0 ) {
						playerShootDirection = player_GetNextPosition (
																			playerCurrentPosition,
																			shootDirection);
						if ( board_FireArrow( currentBoard,
																	playerShootDirection ) ==
																		board_WUMPUS_KILLED ) {
							printf("You killed the wumpus!\n");
							break;
						}
						else if ( board_FireArrow( currentBoard,
																			 playerShootDirection ) ==
																			 	board_ARROW_MISSED ){
							newPlayer.numArrows--;
							printf("Missed. You now have %d arrows.\n", newPlayer.numArrows);
							continue;
						}
						else {
							printf("Unable to fire arrow in that direction.\n");
							continue;
						}
					}
					else {
						printf("You don't have any more arrows to fire\n");
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

Boolean initFunction(Board board, char *userInput, Player player) {
	char *firstChar;
	char *secondChar;
	Position curPosition;
	int positionX, positionY;
	getInput( "At this stage of the program, only two commands are acceptable:\n"
						"init <x>,<y>\n"
						"quit\n\n"
						"Please enter your choice: ",
							userInput,
							sizeof(userInput));

	 firstChar = strtok( userInput, " " );
	if ( firstChar != NULL ) {
		if ( strcmp( firstChar, COMMAND_QUIT ) == 0) {
			/*quit = TRUE;
			break;*/
			return TRUE;
		}
		else {
			secondChar = strtok( NULL, "," );
			if ( secondChar != NULL ) {
				char *thirdChar = strtok( NULL, " " );
				if ( thirdChar != NULL ) {
					positionX = atoi( secondChar );
					positionY = atoi( thirdChar );
					if ( strcmp(firstChar, COMMAND_INIT )==0 &&
							(( positionX<=4 && positionX>=1 ) &&
							 ( positionY<=4 && positionY>=1 ))) {
							 /*playerCurrentPosition*/curPosition.x = positionX;
							 /*playerCurrentPosition*/curPosition.y = positionY;
							 if ( board_PlacePlayer( board,
																			 curPosition ) ==
																				TRUE ) {
								player_Initialise( &player, curPosition );
								printf( "Player Initialized\n" );
								/*break;*/
								return TRUE;
							}
							else {
								printf( "Invalid Space\n\n" );
								/*continue;*/
								return FALSE;
							}
						}
					else {
						printf( "Error 1\n\n" );
						printInvalidInput();
						return FALSE;
					}
				}
				else {
					printf( "Error 2\n\n" );
					printInvalidInput();
					return FALSE;
				}
			}
			else {
				printf( "Error 3\n\n" );
				printInvalidInput();
				return FALSE;
			}
		}
	}
	else {
		printf( "Error 4\n\n" );
		printInvalidInput();
		return FALSE;
	}
}

Boolean loadFunction(Board board, char *userInput ){
	char *firstChar;
	char *secondChar;
	int boardChoice;
	getInput("At this stage of the program, only two commands are acceptable:\n"
					 "load <g>\n"
					 "quit\n\n"
					 "Please enter your choice: ",
						userInput,
						sizeof( userInput ));

	 firstChar = strtok( userInput, " " );
	if ( firstChar != NULL ){
		if ( strcmp( firstChar, COMMAND_QUIT ) == 0 ) {
			return TRUE;
		}
		else {
			secondChar = strtok(NULL, " ");
			if ( secondChar != NULL ) {
				boardChoice = atoi( secondChar );
				if ( strcmp( firstChar, COMMAND_LOAD )==0 &&
							( boardChoice==1 || boardChoice==2 )) {
								OptionLoadBoard( board, boardChoice );
								return TRUE;
							}
				else {
					printInvalidInput();
					return FALSE;
				}
			}
			else {
				printInvalidInput();
				return FALSE;
			}
		}
	}
	else {
		printInvalidInput();
		return FALSE;
	}
}

Position batRandom( Board board, Position playerPosition ) {
	Position randomPosition;
	do {
		randomPosition.x = rand() % BOARD_HEIGHT;
		randomPosition.y = rand() % BOARD_HEIGHT;
	} while( checkEmptySpace( board, randomPosition ) == FALSE );
	board_MovePlayer( board, playerPosition, randomPosition);
	return randomPosition;

}

Boolean checkEmptySpace( Board board, Position position ) {
	if ( board[position.y][position.x] == board_EMPTY ||  board[position.y][position.x] == board_TRAVERSED )
		return TRUE;
	else
		return FALSE;
}

Boolean getDirection( char *userDirectionInput, Direction *tmpDirection ) {
	if ( strcmp( userDirectionInput, COMMAND_NORTH ) == 0 ||
			 strcmp( userDirectionInput, COMMAND_NORTH_SHORTCUT ) == 0 ) {
		*tmpDirection = player_NORTH;
		return TRUE;
	}
	else if ( strcmp(userDirectionInput, COMMAND_SOUTH ) == 0 ||
						strcmp(userDirectionInput, COMMAND_SOUTH_SHORTCUT ) == 0 ) {
		*tmpDirection = player_SOUTH;
		return TRUE;
	}
	else if ( strcmp( userDirectionInput, COMMAND_EAST ) == 0 ||
						strcmp( userDirectionInput, COMMAND_EAST_SHORTCUT ) == 0 ) {
		*tmpDirection = player_EAST;
		return TRUE;
	}
	else if ( strcmp( userDirectionInput, COMMAND_WEST ) == 0 ||
						strcmp( userDirectionInput, COMMAND_WEST_SHORTCUT ) == 0 ) {
		*tmpDirection = player_WEST;
		return TRUE;
	}
	else
		return FALSE;
}

void OptionLoadBoard( Board board, int userLoadChoice ) {
    if ( userLoadChoice == 1 ){
      board_Load( board, BOARD_1) ;
      printf("Board 1 successfully loaded\n\n");
    }
    else {
      board_Load( board, BOARD_2 );
      printf("Board 2 successfully loaded\n\n");
    }

}

void displayGameMenu() {
	printf("\n\n\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
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
