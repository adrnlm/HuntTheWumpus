/*
* COSC1076 Assignment 1, Semester 2 2018
* Student name  : Adrian Lim Song En
* Student number: s3710625
*/
#include "player.h"

void player_Initialise( Player * player, Position position ) {
  player->position = position;
  player->numArrows = INIT_ARROW_COUNT;
}

Position player_GetNextPosition( Position position, Direction direction ){
  switch ( direction ) {
    case 0:
    position.y--;
    break;
    case 1:
    position.x++;
    break;
    case 2:
    position.y++;
    break;
    case 3:
    position.x--;
    break;

  }
  return position;
}

void player_UpdatePosition( Player * player, Position position ) {
  player->position=position;
}
