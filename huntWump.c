/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim Song En
 * Student number: s3710625
 */
#include <stdio.h>
#include <stdlib.h>
#include "huntWump.h"

int main() {
  char userMenuInput[ USER_MAX_INPUT ];
  int menuInput = 0;
    do{
      displayWumpusMenu();
      while (TRUE) {
        char * menuPromt = "Please Enter your choice: ";
        getInput( menuPromt,
                  userMenuInput,
                  USER_MENU_INPUT_PARAMETER ) ;
        menuInput = atoi( userMenuInput );
        if( !( menuInput<4 && menuInput>0 )) {
          printInvalidInput();
          continue;
        }
        else
          break;
      }
        switch( menuInput ) {
          case 1:
            game_PlayGame();
            menuInput = 0;
            break;

          case 2:
            showStudentInformation();
            menuInput = 0;
            break;

          case 3:
            printf("\nGood bye! \n\n");
            break;
        }

    }while( menuInput > 3 || menuInput < 1 );

   return EXIT_SUCCESS;
}

void displayWumpusMenu() {
  printf("\n\n- - - - - - - - - - - - - -\n");
  printf("Welcome to Hunt the Wumpus\n");
  printf("- - - - - - - - - - - - - -\n\n");
  printf("1. Play Game\n");
  printf("2. Show Student Information\n");
  printf("3. Quit\n\n");
}

void showStudentInformation() {
  printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - -");
  printf("\nName: " STUDENT_NAME);
  printf("\nStudent ID: " STUDENT_ID);
  printf("\nStudent Email: " STUDENT_EMAIL);
  printf("\n- - - - - - - - - - - - - - - - - - - - - - - -\n\n");
}
