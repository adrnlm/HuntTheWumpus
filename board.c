/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  :
 * Student number:
 */
#include "board.h"

Board BOARD_1 =
{
   	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_PIT,    board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_BATS,   board_EMPTY,  board_EMPTY,  board_WUMPUS, board_EMPTY},
	{ board_EMPTY,  board_PIT,    board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_BATS,   board_EMPTY,  board_EMPTY}
};

Board BOARD_2 =
{
	{ board_PIT,    board_EMPTY,  board_PIT,    board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_BATS,   board_EMPTY,  board_EMPTY},
	{ board_EMPTY,  board_EMPTY,  board_EMPTY,  board_EMPTY,  board_BATS },
	{ board_EMPTY,  board_WUMPUS, board_EMPTY,  board_EMPTY,  board_EMPTY},
};

void board_Load(Board board, Board boardToLoad) {
   /* TODO */
}

Boolean board_PlacePlayer(Board board, Position position) {
   /* TODO */
   return FALSE;
}


PlayerMove board_MovePlayer(Board board, Position playerPosition, 
			    Position nextPosition) {
   /* TODO */
   return board_PLAYER_MOVED;
}

ArrowHit board_FireArrow(Board board, Position position) {
   /* TODO */
   return board_ARROW_MISSED;
}

void board_Display(Board board) {
   /* TODO */
}

void board_DisplayWarnings(Board board, Position position){
   /* TODO */
}
