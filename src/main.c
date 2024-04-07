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
    char command[50] = "";
    char lastCommand[50] = "";
    char message[] = "Enter a command to start the game";
    char function[3];


    board();
    while (startGame ==1){
        strcpy(lastCommand, handleInput(message, command));
        strcpy(command, lastCommand);
        memcpy(function, command, 2);
    //LD function
        if (strcmp(function, "LD") == 0) {
            strcpy(lastCommand, "LD");
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
        }
    //QQ function
        else if (strcmp(function, "QQ") == 0){
            freeDeck(deck);
            printf("The program exits.");
            exit(0);
        }
    //SW function
        else if (strcmp(function, "SW") == 0){
            displayDynamicInterface(head);
        }

    //"Unknown command" message
        else {
            strcpy(lastCommand, command);
            strcpy(message, "Unknown command.");
        }
    }

}
