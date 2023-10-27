#ifndef GAME_H
#define GAME_H
#include "linkedlist.h"

/* printing the board*/
void display_board(char** board, int rows, int cols);

/* change player position*/
void movePlayer(int* playerX, int* playerY, int rows, int cols, char key, char **board, int* carX, int* carY, LinkedList *list);

/* change car position*/
void moveCar(char **board, int rows, int cols, int *CarX, int *CarY, char *direction);

/* search where the car or player is*/
void search(char c, int* x, int* y, int rows, int cols, char **board);
void searchPlayer(int* playerX, int* playerY, int rows, int cols, char **board);
void searchCar(int* carX, int* carY, int rows, int cols, char **board);


void clear_board();

/* to travel back to previous position */
void undoFunction(int rows, int cols, char **board, LinkedList *history);

/*cheking the state of the game */
int checkGameState(char FinalPos, int playerX, int playerY, int CarX, int CarY);
#endif 
