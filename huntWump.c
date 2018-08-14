/*
 * COSC1076 Assignment 1, Semester 2 2018
 * Student name  : Adrian Lim
 * Student number: s3710625
 */
#include <stdio.h>
#include <stdlib.h>
#include "huntWump.h"

#include "board.c"
#include "game.c"
#include "helpers.c"
#include "player.c"


int main() {
  int menuInput=0;
   /**
    * Here's the main function. You can write the "main menu" loop/code
    * here or you can make separate functions - up to you.
    */
    do{
      printf("\n\n- - - - - - - - - - - - - -\n");
      printf("Welcome to Hunt the Wumpus\n");
      printf("- - - - - - - - - - - - - -\n\n");
      printf("1. Play Game\n");
      printf("2. Show Student Information\n");
      printf("3. Quit\n\n");

      printf("Please Enter your choice: ");
      scanf("%d", &menuInput);
      if(!(menuInput<4 && menuInput>0)) {
        printf("- - - - - - - - - - - - - -\n\n");
        printf("    Invalid input.\n\n");
      }
      else {
        switch(menuInput) {
          case 1:
            game_PlayGame();
            menuInput=0;
            break;

          case 2:
            showStudentInformation();
            menuInput=0;
            break;

          case 3:
            printf("\nGood bye! \n\n");
            break;
        }
      }
    }while(menuInput > 3 || menuInput < 1);


   return EXIT_SUCCESS;
}

void showStudentInformation() {
  printf("\n\n- - - - - - - - - - - - - - - - - - - - - - - -");
  printf("\nName: " STUDENT_NAME);
  printf("\nStudent ID: " STUDENT_ID);
  printf("\nStudent Email: " STUDENT_EMAIL);
  printf("\n- - - - - - - - - - - - - - - - - - - - - - - -\n\n");
}
