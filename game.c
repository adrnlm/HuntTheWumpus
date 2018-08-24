/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim Song En
 * Student number: s3710625
 */
#include "game.h"

void game_PlayGame(){
	Board currentBoard;
	char userEnterInput[USER_MAX_INPUT];
	char userLoadInput [MAX_LOAD_INPUT];
	char userInitInput [MAX_INIT_INPUT];
	char userPlayInput [MAX_PLAY_INPUT];
	Player newPlayer;
	int quit=FALSE;
	displayGameMenu();
	getInput("Press enter to continue...", userEnterInput, USER_MAX_INPUT);
	/*LOAD OPTION*/
	while ( quit==FALSE ) {
		Process loadChoice = loadFunction(currentBoard, userLoadInput);
		if ( loadChoice == process_fail ) {
			printInvalidInput();
			continue;
		}
		else if ( loadChoice == process_quit )
			return;
		else
			break;
	}
	/*INIT OPTION*/
	while ( quit==FALSE ) {
		Process initChoice = initFunction(currentBoard, &newPlayer, userInitInput);
		if ( initChoice == process_fail ) {
			printInvalidInput();
			continue;
		}
		else if ( initChoice == invalid_space ) {
			printf("Invalid Space\n\n");
			continue;
		}
		else if ( initChoice == process_quit )
			return;
		else
			break;
	}
	/*PLAY OPTIONS*/
	while ( quit==FALSE ) {
		Process playChoice = playFunction(currentBoard, &newPlayer, userPlayInput);
		if ( playChoice == process_fail ) {
			printInvalidInput();
			continue;
		}
		if ( playChoice == process_end ) {
			return;
		}
		else if ( playChoice == process_success || playChoice == invalid_space)
			continue;
		else
			return;
	}
	srand(0);
}

/*Checks if the player input is a valid choice*/
Choice playerChoice(char * input) {
	if ( strncmp(input, COMMAND_QUIT, USER_MAX_INPUT) == 0 )
		return choice_quit;
	else if ( strncmp(input, COMMAND_LOAD, USER_MAX_INPUT) == 0 )
		return choice_load;
	else if ( strncmp(input, COMMAND_INIT, USER_MAX_INPUT) == 0)
		return choice_init;
	else if ( strncmp(input, COMMAND_SHOOT, USER_MAX_INPUT) == 0 )
		return choice_shoot;
	else
		return choice_invalid;
}

/*This does the load function of the game*/
Process loadFunction(Board board, char *loadInput ){
	char *firstChar;
	char *secondChar;
	int boardChoice;
	getInput(displayLoadMenu, loadInput, MAX_LOAD_INPUT);

	if ( playerChoice(loadInput) == 0 ) {
		return process_quit;
	}
	firstChar = strtok( loadInput, " " );
	secondChar = strtok(NULL, "\n");
	if ( firstChar != NULL ) {
		if ( playerChoice(firstChar) == choice_load && secondChar != NULL ) {
			boardChoice = atoi ( secondChar );
			if ( boardChoice == 1 || boardChoice == 2 ) {
				OptionLoadBoard(board, boardChoice);
				return process_success;
			}
			else
				return process_fail;
		}
		else
			return process_fail;
	}
	else
		return process_fail;
}

/*Initialize function of the game*/
Process initFunction(Board board, Player * player, char *initInput) {
	char *firstChar;
	char *secondChar;
	char *thirdChar;
	Position curPosition;
	int positionX, positionY;
	getInput(displayInitMenu, initInput, MAX_INIT_INPUT);
		if ( playerChoice(initInput) == choice_quit )
			return process_quit;
			firstChar  = strtok( initInput, " " );
			secondChar = strtok( NULL, "," );
			thirdChar  = strtok( NULL, "\n" );
		if ( firstChar != NULL) {
		if ( playerChoice(firstChar)==choice_init && ((secondChar != NULL) && (thirdChar != NULL))) {
			positionX = atoi( secondChar );
			positionY = atoi( thirdChar );
			if ( checkBoundaries(positionX, positionY)) {
				curPosition.x = positionX;
				curPosition.y = positionY;
				if (board_PlacePlayer(board, curPosition)==TRUE){
					player_Initialise(player, curPosition);
					printf( "Player Initialized\n" );
					return process_success;
				}
				else
					return invalid_space;
			}
			else
			return process_fail;
		}
		else
		return process_fail;
	}
	else
	return process_fail;

}

/*The actual game*/
Process playFunction(Board board, Player * player, char *playInput) {
	char * firstChar;
	char * secondChar;
	MoveResults moveResult;
	Direction moveDirection, shootDirection;
	Position playerCurrentPosition, playerNextPosition;
	playerCurrentPosition = player->position;
	board_Display( board );
	board_DisplayWarnings ( board, playerCurrentPosition );
	getInput(displayPlayMenu, playInput, MAX_PLAY_INPUT);
	if ( playerChoice(playInput) == choice_quit )
		return process_quit;
	firstChar = strtok( playInput, " ");
	secondChar = strtok(NULL, " \n");
	if ( firstChar != NULL ) {
		if ( getDirection(firstChar, &moveDirection)){
			playerNextPosition = player_GetNextPosition( playerCurrentPosition, moveDirection );
			moveResult = move(board, player, playerCurrentPosition, playerNextPosition);
			if ( moveResult == killed )
				return process_end;
			else if ( moveResult == out_of_bounds)
				return invalid_space;
			else
				return process_success;
		}
		else if ( playerChoice(firstChar) == choice_shoot && getDirection(secondChar, &shootDirection) ) {
			if ( shoot(board, player, shootDirection))
				return process_end;
		}
		else
			return process_fail;
	}
	else
		return process_fail;
}

/*Function to check movement in game and return a result*/
MoveResults move( Board board, Player * player, Position curPos, Position nextPos ){
	if ( board_MovePlayer( board, curPos, nextPos) == board_PLAYER_MOVED ) {
		printf("Player moved.\n");
		player_UpdatePosition ( player, nextPos);
		return moved;
	}
	else if ( board_MovePlayer( board, curPos, nextPos) == board_BAT_CELL ) {
		printf("Bat Cell!\n");
		batRandom(board, player);
		return moved;
	}
	else if ( board_MovePlayer( board,
															curPos,
															nextPos ) ==
																board_OUTSIDE_BOUNDS ) {
		printf("Unable to move - outside bounds.\n");
		return out_of_bounds;
	}
	else  {
		printf("Player killed!\n");
		return killed;
	}
}

/*Function to randomize player current position when player enter a bat cell*/
void batRandom( Board board, Player * player ) {
	Position randomPosition;
	Position playerPosition;
	playerPosition = player->position;
	do {
		randomPosition.x = rand() % BOARD_HEIGHT;
		randomPosition.y = rand() % BOARD_HEIGHT;
	} while( checkEmptySpace( board, randomPosition ) == FALSE );
	board_MovePlayer( board, playerPosition, randomPosition);
	player_UpdatePosition( player, randomPosition);
}

/*Function for shooting in game*/
Boolean shoot(Board board, Player *player, Direction shootD ) {
	Position playerShootD;
	if ( player->numArrows>0 ) {
		playerShootD = player_GetNextPosition (
			player->position,
			shootD);
			if ( board_FireArrow( board,
				playerShootD ) ==
				board_WUMPUS_KILLED ) {
					printf("You killed the wumpus!\n");
					return TRUE;
				}
				else if ( board_FireArrow( board,
					playerShootD ) ==
					board_ARROW_MISSED ){
						player->numArrows--;
						printf("Missed. You now have %d arrows.\n", player->numArrows);
						return FALSE;
					}
					else {
						printf("Unable to fire arrow in that direction.\n");
						return FALSE;
					}
				}
				else {
					printf("You don't have any more arrows to fire\n");
					return FALSE;
				}
			}

/*Function to check if the entered coordinates is within the board boundaries*/
Boolean checkBoundaries(int x, int y) {
	if ((x>=0 && x<BOARD_WIDTH) && (y>=0 && y<BOARD_HEIGHT))
		return TRUE;
	else
		return FALSE;
}

/*Check if the next position is a empty space or traversed space*/
Boolean checkEmptySpace( Board board, Position position ) {
	if ( board[position.y][position.x] == board_EMPTY ||  board[position.y][position.x] == board_TRAVERSED )
		return TRUE;
	else
		return FALSE;
}

/*Function to convert user input to a direction command*/
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

/*Function to load whichever board the user chooses*/
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

/*Prints out the display menu*/
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
