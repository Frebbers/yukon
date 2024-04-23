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
    int len;
    Card *deck = NULL;
    Card *head = NULL;

    char command[50] = "";
    char lastCommand[50] = "";

    char *message = "Enter a command to start the game";
    char function[9]= " ";
    int counter = 0;

    char ld[]= "LD";
    char p[]= "P";
    char move[]= "C&d:&d%c->C&d";




    board();
    while (startGame == 1){
        strcpy(lastCommand, handleInput(message, command));
        strcpy(command, lastCommand);
        sscanf(command, "%9s", function); // Extract function name from command
        memcpy(function, command, strlen(function));
        function[strlen(function)] = '\0'; // Ensure function is null-terminated
        printf("Function is %s\n", function);
        printf("length of function is %llu\n", strlen(function));
        printf("%c",function[1]);


    //LD function
        if (strcmp(function, ld) == 0){
           // strcpy(lastCommand, "LD");
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

        else if (strcmp(function, "P") == 0) {
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
    //scan the command for the source column and the destination column
        else if (function[0]=='C' &&

                    function[2]==':' &&


                        function[5]=='-' &&
                         function[6]=='>' &&
                          function[7]=='C')

            {

            int sourceColumn=convertValue(function[1]);;
            char sourceValue=function[3];
            char sourceSuit=function[4];
            int destColumn=convertValue(function[8]);
            Column** columns= dealCards(head);
            printColumns(columns);

            moveCard(&columns[sourceColumn-1], &columns[destColumn-1], sourceValue, sourceSuit);
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

