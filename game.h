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
#define USER_MAX_INPUT ( EXTRA_SPACES + 10 )
#define MAX_LOAD_INPUT ( EXTRA_SPACES + 6 )
#define MAX_INIT_INPUT ( EXTRA_SPACES + 8 )
#define MAX_PLAY_INPUT ( EXTRA_SPACES + 7 )

#define displayLoadMenu "At this stage of the program, only two commands are acceptable:\nload <g>\nquit\n\n Please enter your choice: "
#define displayInitMenu "At this stage of the program, only two commands are acceptable:\ninit <x>,<y>\nquit\n\nPlease enter your choice: "
#define displayPlayMenu "\n\nAt this stage of the program, only three commands are acceptable:\n<directions>\nshoot <directions>\nquit\nWhere <direction> is one of: north,n,south,s,east,e,west,w\n\nPlease enter your choice: "

typedef enum choice {
  choice_quit, /*0*/
  choice_load, /*1*/
  choice_init, /*2*/
  choice_shoot, /*3*/
  choice_invalid /*4*/
} Choice;

typedef enum process {
  process_fail,
  process_quit,
  process_success,
  invalid_space,
  process_end
} Process;

typedef enum moveResults {
  moved,
  killed,
  out_of_bounds
} MoveResults;

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

Choice playerChoice();

Process loadFunction();

Process initFunction();

Process playFunction();

MoveResults move();

void batRandom();

Boolean shoot();

Boolean checkBoundaries();

Boolean checkEmptySpace();

Boolean getDirection();

void OptionLoadBoard();

void displayGameMenu();



#endif
