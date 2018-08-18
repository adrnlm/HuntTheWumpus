/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim
 * Student number: s3710625
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
  int height, width;
  for (width=0; width < BOARD_WIDTH; width++){
    for (height=0; height < BOARD_HEIGHT; height++) {
      board[width][height]=boardToLoad[width][height];
    }
  }
}

Boolean board_PlacePlayer(Board board, Position position) {
   if (board[position.y][position.x]==board_EMPTY) {
     board[position.y][position.x]=board_PLAYER;
     return TRUE;
   }
  else
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
   int row, column;
   printf("\n     0    1    2    3    4  \n");
   for (row = 0; row < BOARD_WIDTH; row++) {
      printf("  --------------------------\n");
      printf("%d", row);
        for (column = 0; column < BOARD_HEIGHT; column++) {
          if (board[row][column]==board_PIT)
            printf(" | %s", PIT_OUTPUT);
          else if (board[row][column]==board_BATS)
            printf(" | %s", BATS_OUTPUT);
          else if (board[row][column]==board_WUMPUS)
              printf(" | %s", WUMPUS_OUTPUT);
          else if (board[row][column]==board_PLAYER)
            printf(" | %s", PLAYER_OUTPUT);
          else
            printf(" | %s", EMPTY_OUTPUT);
        }
        printf(" |\n");
    }

}

void board_DisplayWarnings(Board board, Position position){
  int scanX = position.x-1;
  int scanY = position.y-1;
  int maxScanX = position.x+1;
  int maxScanY = position.y+1;
  char *warning[]=
  {"You hear flapping!", "You feel a breeze!", "You smell a wumpus!"};

  for ( int loopX = scanX; loopX>=0 && (loopX<=maxScanX && loopX<BOARD_WIDTH)  ; loopX++ ){
    for ( int loopY = scanY; loopY>=0 && (loopY<=maxScanY && loopY<BOARD_HEIGHT) ; loopY++ ) {
      int warningType = 2;
        do {
          if ( board[loopY][loopX] == warningType){
            /*TESTING
            printf("\nboard[%d][%d]", loopX, loopY );*/
            printf("%s | ", warning[warningType-2]);
        }
        warningType++;
      } while(warningType<5);
    }
  }
}
