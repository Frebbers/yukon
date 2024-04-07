#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include "SW.h"
#include "carddeck.h"
#include "board.h"







int main() {
    int startGame = 1;
    int quitGame = 0;
    Card *deck = NULL;
    Card *head = NULL;
    char input[50] = "";
    char lastCommand[50] = "";
    char message[] = "Enter a command to start the game";
    char function[3];


    while (startGame == 1){
        board();
        strcpy(lastCommand, handleInput(message, input));
        strcpy(input, lastCommand);
        memcpy(function, input, 2);


        if (strcmp(function, "SW") == 0) {
            strcpy(lastCommand, "SW");
            const char *filename = "rsc/cards.txt";
            Card* newDeck = loadDeck(filename);
            if (newDeck != NULL) {
                if (deck != NULL) {
                    freeDeck(deck);
                }
                deck = newDeck;
                head = deck;
                strcpy(message, "OK");
            } else {
                strcpy(message, "Error: No deck loaded.");
            }

            displayDynamicInterface(head);

        // Quit the game
        } else if (strcmp(function,"QQ") == 0){
            freeDeck(deck);
            printf("The program exits.");
            exit(0);

        // Unknown command.
        } else {
            strcpy(lastCommand, function);
            strcpy(message, "Unknown command.");
        }
    }


}
