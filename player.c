/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim
 * Student number: s3710625
 */
#include "player.h"

void player_Initialise(Player * player, Position position){
   player->position.x = position.x;
   player->position.y = position.y;
   player->numArrows = INIT_ARROW_COUNT;
}


Position player_GetNextPosition(Position position, Direction direction){
   /* TODO */
   return position;
}

void player_UpdatePosition(Player * player, Position position) {
   /* TODO */
}
