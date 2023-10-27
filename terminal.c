#include <stdio.h>
#include <termios.h>
#include "terminal.h"

void disableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void enableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

void printInstructions(){
    printf("press w to move up\n");
    printf("press s to move down\n");
    printf("press a to move left\n");
    printf("press d to move down\n");
    printf("press u to undo\n");

}