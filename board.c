/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim Song En
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

void board_Load( Board board, Board boardToLoad ) {
  int height, width;
  for ( width=0; width < BOARD_WIDTH; width++ ){
    for ( height=0; height < BOARD_HEIGHT; height++ ) {
      board[width][height] = boardToLoad[width][height];
    }
  }
}

Boolean board_PlacePlayer( Board board, Position position ) {
   if ( board[position.y][position.x] == board_EMPTY ) {
     board[position.y][position.x] = board_PLAYER;
     return TRUE;
   }
  else
   return FALSE;
}

PlayerMove board_MovePlayer( Board board, Position playerPosition, Position nextPosition ) {
   if ( board[nextPosition.y][nextPosition.x] == board_PIT ||
        board[nextPosition.y][nextPosition.x] == board_WUMPUS ) {
     return board_PLAYER_KILLED;
   }
   else if ( nextPosition.y >= BOARD_HEIGHT ||
             nextPosition.x >= BOARD_WIDTH ||
            nextPosition.x < 0 ||
            nextPosition.y < 0 ) {
              return board_OUTSIDE_BOUNDS;
   }
   else if ( board[nextPosition.y][nextPosition.x] == board_EMPTY ||
             board[nextPosition.y][nextPosition.x] == board_TRAVERSED ) {
     board[nextPosition.y][nextPosition.x] = board_PLAYER;
     board[playerPosition.y][playerPosition.x] = board_TRAVERSED;
     return board_PLAYER_MOVED;
   }
   else {
     return board_BAT_CELL;
   }
}

ArrowHit board_FireArrow( Board board, Position position ) {
   if ( position.y >= BOARD_HEIGHT ||
        position.x >= BOARD_WIDTH ||
        position.x < 0 ||
        position.y < 0 )
    return board_ARROW_OUTSIDE_BOUNDS;
  else if ( board[position.y][position.x] == board_WUMPUS )
    return board_WUMPUS_KILLED;
  else
   return board_ARROW_MISSED;
}

void board_Display( Board board ) {
   int row, column;
   printf("\n\n    0  1  2  3  4  \n");
   for ( row = 0; row < BOARD_WIDTH; row++ ) {
      printf("  ----------------\n");
      printf("%d ", row);
        for ( column = 0; column < BOARD_HEIGHT; column++ ) {
          if ( board[row][column] == board_PLAYER )
            printf("|%s", PLAYER_OUTPUT);
          else if ( board[row][column] == board_TRAVERSED )
            printf("|%s", TRAVERSED_OUTPUT);
          else
            printf("|%s", EMPTY_OUTPUT);
        }
        printf("|\n");
    }
    printf("  ----------------\n");

}

void board_DisplayWarnings( Board board, Position position ) {
  int loopX;
  int loopY;
  int maxScanX = position.x+1;
  int maxScanY = position.y+1;
  int warningType;
  char *warning[] = { "You hear flapping!",
                      "You feel a breeze!",
                      "You smell a wumpus!" };
  Boolean checkPrint[] = { FALSE, FALSE, FALSE };

  for ( loopX = position.x-1; loopX<=maxScanX && loopX<BOARD_WIDTH; loopX++ ) {
    for ( loopY = position.y-1; loopY<=maxScanY && loopY<BOARD_HEIGHT; loopY++ ) {
      warningType = 2;
        do {
          if ( board[loopY][loopX] == warningType && checkPrint[warningType-2] == FALSE ) {
            printf("%s ", warning[warningType-2]);
            checkPrint[warningType-2] = TRUE;
        }
        warningType++;
      } while( warningType<5 );
    }
  }
}
