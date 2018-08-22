/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim Song En
 * Student number: s3710625
 */
#ifndef GAME_H
#define GAME_H

#include "helpers.h"
#include "board.h"
#include "player.h"

#define COMMAND_LOAD "load"
#define COMMAND_INIT "init"
#define COMMAND_NORTH "north"
#define COMMAND_NORTH_SHORTCUT "n"
#define COMMAND_SOUTH "south"
#define COMMAND_SOUTH_SHORTCUT "s"
#define COMMAND_EAST "east"
#define COMMAND_EAST_SHORTCUT "e"
#define COMMAND_WEST "west"
#define COMMAND_WEST_SHORTCUT "w"
#define COMMAND_SHOOT "shoot"
#define COMMAND_QUIT "quit"
#define USER_MAX_INPUT 10
#define MAXIMUM_QUIT_INPUT 4
#define MAXIMUM_LOAD_INPUT 6
#define MAXIMUM_INIT_INPUT 8
#define MAXIMUM_PLAY_INPUT 11
#define MAXIMUM_QUIT_PARAMETERS (EXTRA_SPACES + MAXIMUM_QUIT_INPUT)
#define MAXIMUM_LOAD_PARAMETERS (EXTRA_SPACES + MAXIMUM_LOAD_INPUT)
#define MAXIMUM_INIT_PARAMETERS (EXTRA_SPACES + MAXIMUM_INIT_INPUT)
#define MAXIMUM_PLAY_PARAMETERS (EXTRA_SPACES + MAXIMUM_PLAY_INPUT)

typedef enum choice {
  choice_quit, /*0*/
  choice_load, /*1*/
  choice_init, /*2*/
  choice_shoot, /*3*/
  choice_north, /*4*/
  choice_south, /*5*/
  choice_east, /*6*/
  choice_west, /*7*/
  choice_invalid /*8*/
} Choice;

/**
 * Main menu option 1 - play the game as per the specification.
 *
 * This function makes all the calls to board & player and handles interaction
 * with the user (reading input from the console, error checking, etc...).
 *
 * It should be possible to break this function down into smaller functions -
 * but this is up to you to decide and is entirely your own design. You can
 * place the additional functions in this header file if you want.
 *
 * Note that if you don't break this function up it could become pretty big...
 * and marks are allocated to good coding practices.
 */
void game_PlayGame();

/**
 * Gets direction from user input and assign that to a temporary position and
 * return true
 */
Boolean getDirection();

/**
 * Checks for empty spaces for player to move and return true/ false
 */
Boolean checkEmptySpace();

/**
 *Load stated board by the user
 */
void OptionLoadBoard();

/**
 *Prints out the display menu
 */
void displayGameMenu();

Position batRandom();

Boolean loadFunction();

Boolean initFunction();

#endif
