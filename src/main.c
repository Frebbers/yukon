#include <stdio.h>
#include "stdlib.h"
#include "carddeck.h"
#include "board.h"

int main() {
    int startGame = 1;
    char command[50] = ""; // Defines the maximum length available,
    char lastCommad[50] = "";
    char* message = "Enter a command to start the game";

    while(startGame==1) {
        board();
        strcpy(lastCommad, handleInput(message, command));
        strcpy(command, lastCommad);
    }

}

