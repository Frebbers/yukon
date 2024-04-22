#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include "SW.h"
#include "carddeck.h"
#include "board.h"
#include "LD.h"
#include "SR.h"
#include "Phases.h"



int main() {
    int startGame = 1;
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
        sscanf(command, "%2s", function);
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

        }
        //QQ function
        else if (strcmp(function,"QQ") == 0) {
            saveDeck(head, "rsc/savedcards.txt");

            freeDeck(deck);
            printf("The program exits.");
            exit(0);

        }
            //P function
        else if (strcmp(function,"P") == 0){
            if (deck != NULL) {
                dealCards(head);
             //   dealCards(head); // Deal cards from the deck into columns
                message = "OK";
              //  playPhase(&head); // Enter into the play phase
            } else {
                message = "Error: No deck loaded.";
            }
        }

    //Move cards
        else if (strcmp(function, "M") == 0) {
            Column** columns= dealCards(head);
            printColumns(columns);

            moveCard(&columns[2], &columns[3], '3', 'C');
            printColumns(columns);


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
