#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <string.h>

 /* Display the board*/
void display_board(char** board, int rows, int cols) {
    int i;
    int j;

    for (i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            putchar(board[i][j]);
        }
        putchar('\n');
    }
}

/* determines if a Coordinates is within the board's boundaries*/ 
int is_valid_position(char** board,int x, int y, int rows, int cols) {
    return x >= 0 && x < rows && y >= 0 && y < cols && board[x][y] != '*';
}

/* checking if game ended*/
int checkGameState(char FinalPos, int playerX, int playerY, int CarX, int CarY) {
    if (playerX == CarX && playerY == CarY) {
        return -1; /*Player was hit by the car*/
    }

    if (FinalPos == 'G') {
        return 1; /* Player reached the goal*/
    }

    return 0; /*Game is still ongoing*/ 
}

/* cars movements are here*/
void moveCar(char **map, int rows, int cols, int *carX, int *carY, char *direction) 
{
    int newX = *carX;
    int newY = *carY;

    /*Determine the new position based on the current direction*/
    switch(*direction) {
        case '^':newY--;break;
        case '>':newX++;break;
        case 'v':newY++;break;
        case '<':newX--;break;
    }

    /*Check if the new position is within the boundaries of the map*/
    char nextTile = (newX >= 0 && newX < cols && newY >= 0 && newY < rows) ? map[newY][newX] : ' ';
    
    /*If the next tile is a valid tile for the car to move to, update the car's position and return*/
    if (nextTile == '.' || nextTile == '>' || nextTile == 'P' || nextTile == 'G') {
        *carX = newX;
        *carY = newY;
        return;
    }

    int leftX = *carX, leftY = *carY, rightX = *carX, rightY = *carY;
    char leftDir, rightDir;

    /*Determine the left and right positions based on the current direction*/
    switch(*direction) {
        case '^':
            leftX--;
            rightX++;
            leftDir = '<';
            rightDir = '>';
            break;
        case '>':
            leftY--;
            rightY++;
            leftDir = '^';
            rightDir = 'v';
            break;
        case 'v':
            leftX++;
            rightX--;
            leftDir = '>';
            rightDir = '<';
            break;
        case '<':
            leftY++;
            rightY--;
            leftDir = 'v';
            rightDir = '^';
            break;
    }

    /*If the left position is a valid tile for the car to move to, update the car's position and direction and return*/
    if (leftX >= 0 && leftX < cols && leftY >= 0 && leftY < rows && map[leftY][leftX] == '.') {
        *carX = leftX;
        *carY = leftY;
        *direction = leftDir;
        return;
    }

    /*If the right position is a valid tile for the car to move to, update the car's position and direction and return*/
    if (rightX >= 0 && rightX < cols && rightY >= 0 && rightY < rows && map[rightY][rightX] == '.') {
        *carX = rightX;
        *carY = rightY;
        *direction = rightDir;
        return;
    }
}


/**
 * Moves the player on the board based on the key pressed and updates the player's position.
 * If the key is 'u', it undoes the last move by calling the undoFunction.
 * If the new position is within the board and not a '*', it updates the player's position.
 * If the key is not 'u', it inserts the current board state into the history LinkedList.
 */
void movePlayer(int* playerX, int* playerY, int rows, int cols, char key, char **board, int* carX, int* carY, LinkedList *history) 
{
    int newX = *playerX;
    int newY = *playerY;
    int i;

    switch (key){
        case 'w':newY--;break;
        case 's':newY++;break;
        case 'a':newX--;break;
        case 'd':newX++;break;
        case 'u':
            /* restoring the game board to previous state */
            undoFunction(rows, cols, board, history);
            /* find player and car positions and update the board */
            searchPlayer(playerX, playerY, rows, cols, board);
            searchCar(carX, carY, rows, cols, board);
            return;
        default:
            break;
    }
    /* check if coordinates are within the boundaries */
    if (newX >= 0 && newX < cols && newY >= 0 && newY < rows && board[newY][newX] != '*') {
        *playerX = newX;
        *playerY = newY;
    }

    /*If the key is not 'u', insert the current board state into the history LinkedList*/ 
    if (key != 'u'){
        for(i = 0; i < rows; i++){
            insertLastNode(history, board[i], (sizeof(char) * cols));
        }
    }
}

/* undo function to go back to previous position */
void undoFunction(int rows, int cols, char **board, LinkedList *history){
    int i;
    char* data;

    for (i = rows-1; i >= 0; i--)
    {
        data = removeTailNode(history);
        if (data != NULL){
            memcpy(board[i], data, sizeof(char) * cols);
        } 
        free(data);
    }
}

/* search for a given c */
void search(char c, int* x, int* y, int rows, int cols, char **board)
{
    int i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < cols; j++){
            if (board[i][j] == c)  {
                *x = i; 
                *y = j; 
                return;
            } 
        }
    }
}

/* used to search where the player is */
void searchPlayer(int* playerX, int* playerY, int rows, int cols, char **board)
{
    search('P', playerX, playerY, rows, cols, board);
}

/* used to search where the car is */
void searchCar(int* carX, int* carY, int rows, int cols, char **board)
{
    search('^', carX, carY, rows, cols, board);
    if (*carX == -1 && *carY == -1){
        search('>', carX, carY, rows, cols, board);
    }if (*carX == -1 && *carY == -1){
        search('v', carX, carY, rows, cols, board);
    }if (*carX == -1 && *carY == -1){
        search('<', carX, carY, rows, cols, board);
    }
}

void clear_board() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}