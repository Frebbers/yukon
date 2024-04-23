#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include "SW.h"
#include "carddeck.h"
#include "board.h"
#include "LD.h"
#include "SR.h"
#include "SI.h"


int main() {
    int startGame = 1;
    int quitGame = 0;
    Card *deck = NULL;
    Card *head = NULL;
    char command[50] = "";
    char lastCommand[50] = "";
    char *message = "Enter a command to start the game";
    char function[3];


    board();
    while (startGame == 1){
        strcpy(lastCommand, handleInput(message, command));
        strcpy(command, lastCommand);
        memcpy(function, command, 2);
    //LD function
        if (strcmp(function, "LD") == 0) {
            strcpy(lastCommand, "LD");
            const char *filename = "rsc/cards.txt";
            Deck* newDeck = loadDeck(filename);
            if (newDeck != NULL) {
                if (deck != NULL) {
                    freeDeck(deck);
                }
                deck = newDeck;
                head = deck;
                loadedDeck();
                message = "OK";
            } else {
                board();
                message= "Error: No deck loaded.";
            }
        } else if (strcmp(function,"QQ") == 0){
           saveDeck(head,"rsc/savedcards.txt");

            freeDeck(deck);
            printf("The program exits.");
            exit(0);
        }
    //SR function
        else if (strcmp(function, "SR") == 0){
            Card *newDeck = SR(head);
            if (newDeck != NULL) {
                if (deck != NULL) {
                    freeDeck(deck);
                }
                deck = newDeck;
                head = deck;
                loadedDeck();
                message = "OK";
            } else {
                board();
                message= "Error";
            }
        }
        //SI function
        else if (strcmp(function,"SI") == 0){
            Card* newDeck = splitShuffle( head);
            if (newDeck != NULL) {
                if (deck != NULL) {
                //    freeDeck(deck);
                }
                deck = newDeck;
                 head = deck;
                //head = newDeck;
                loadedDeck();
                message = "OK";
            } else {
                board();
                message= "Error: No deck loaded.";
            }

        }
    //SW function
        else if (strcmp(function, "SW") == 0){
            message = displayDynamicInterface(head);

        }

    //"Unknown command" message
        else {
            strcpy(lastCommand, command);
            message = "Unknown command.";
        }
    }

}
