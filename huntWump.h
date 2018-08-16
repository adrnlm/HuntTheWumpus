/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim
 * Student number: s3710625
 */
#ifndef HUNTWUMP_H
#define HUNTWUMP_H

#include "helpers.h"
#include "game.h"

#define STUDENT_NAME "Adrian Lim Song En"
#define STUDENT_ID "s3710625"
#define STUDENT_EMAIL "s3710625@student.rmit.edu.au"
#define USER_MAX_MENU_INPUT 1
#define USER_MENU_INPUT_PARAMETER (USER_MAX_MENU_INPUT + EXTRA_SPACES)

/**
 * Main menu option 2 - show your student information as per specification.
 *
 * You should change the defines above related to student information and use
 * them when printing.
 */
void showStudentInformation();

void playGame();

#endif
