#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include "SW.h"
#include "carddeck.h"
#include "board.h"
#include "LD.h"
#include "SR.h"
void dealCards(Card** deck) {
    const int columnSizes[7] = {1, 6, 7, 8, 9, 10, 11};
    for (int i = 0; i < 7; i++) {
        printf("C%d ", i + 1);
        for (int j = 0; j < columnSizes[i]; j++) {
            if (*deck != NULL) {
                Card* card = removeCard(deck);  // Function to remove and return the top card from the deck
                printf("[%c%c] ", card->value, card->suit);
                // Place the card into the appropriate column, manage face-down or face-up based on rules
            }
        }
        printf("\n");
    }
}

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
                loadedDeck();
                message = "OK";
            } else {
                board();
                message= "Error: No deck loaded.";
            }
        } else if (strcmp(function,"QQ") == 0) {
            saveDeck(head, "rsc/savedcards.txt");

            freeDeck(deck);
            printf("The program exits.");
            exit(0);
        } else if (strcmp(function,"PP") == 0){
            if (deck != NULL) {
                dealCards(&head); // Deal cards from the deck into columns
                message = "OK";
            } else {
                message = "Error: No deck loaded.";
            }
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
