#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "linkedlist.h"
#include "terminal.h"

/* main function */
int main(int argc, char *argv[]) 
{
    FILE* file;
    int i;
    int j;
    int previousX;
    int previousY;
    int rows;
    int cols;
    int playerX;
    int playerY;
    int CarX;
    int CarY; 
    char direction = ' '; 
    int temp;

    /* checking arguments*/
    if (argc != 2) {
            printf("Incorrect number of arguments.\n");
            return 1;
    }

    /* opening the file*/
    char *filename = argv[1];
    file = fopen(filename, "r");
    if (!file) {
        printf("Error opening the file.\n");
        return 1;
    }

    /*reading rows and cols*/
    fscanf(file, "%d %d", &rows, &cols);

    /*allocating memory to the board */
    char** board =(char**) malloc(rows * sizeof(char *));
    for (i = 0; i < rows; i++) {
        board[i] = (char*) malloc(cols * sizeof(char));
    }
    /* creating the board */
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (fscanf(file, "%d", &temp) == 1) {
                if (temp == 0) {
                    if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                        board[i][j] = '*';
                    } else {
                        board[i][j] = ' ';
                    }
                } else {
                    switch (temp) {
                        case 1:board[i][j] = '.';break;
                        case 2:board[i][j] = '>';break;
                        case 3:board[i][j] = 'P';break;
                        case 4:board[i][j] = 'G';break;
                    }
                }
            } 
        }
    }
    /* close the file */
    fclose(file);
    
    /* find the car position and player position*/
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (board[i][j] == '>') {  
                CarX = j;
                CarY = i;
                direction = '>';  
            } else if (board[i][j] == 'P') {
                playerX = j;
                playerY = i;
            }
        }
    }

    char FinalPos = ' ';

    LinkedList* history; 
    /* linked list to store previous positions */
    history = (LinkedList*) calloc(1, sizeof(LinkedList));
    disableBuffer();

    /*---------DO WHILE LOOP-----------*/
    do {
        clear_board();
        display_board(board,rows, cols);
        printInstructions();
        char key = getchar();
        /* user can exit if q is pressed */
        if (key == 'q') {
            break;
        }
        clear_board();
        /* last position of the player*/
        previousX = playerX;
        previousY = playerY;

        /*---------player----------*/
        movePlayer(&playerX,&playerY, rows, cols, key, board, &CarX, &CarY, history);

        /* old position get updated in the board*/
        board[previousY][previousX] = FinalPos;

        /* player's new position can be a dot or a space */
        FinalPos = board[playerY][playerX];

        /*update game board with new position of player P*/
        board[playerY][playerX] = 'P';
        /*-------------------------*/

        /*---------car----------*/
        /*old position is changed to a dot*/
        board[CarY][CarX] = '.';
        /* getting the new direction of the car*/
        moveCar(board, rows, cols, &CarX, &CarY, &direction);
        /* setting that new direction*/
        board[CarY][CarX] = direction;
        /*-------------------------*/

        /* cheking the state of the game*/
        int gameState = checkGameState(FinalPos, playerX, playerY, CarX, CarY);
        if (gameState == -1) {
            printf("Sorry, you were hit by the car.\n");
            break;
        }

        if (gameState == 1) {
            printf("Congratulations! You reached the goal.\n");
            break;
        }
        /*-------------------------*/
        display_board(board,rows, cols);
        printInstructions();
    } while (1);

    /* free the memory used by the linkedlist */
    FreeMemory(history);
    
    /* free the memory used by the board */
    for (i = 0; i < rows; i++) {
        free(board[i]);
    }
    free(board);
    
    return 0;
}
