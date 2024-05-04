#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SW.h"
#include "carddeck.h"
#include "board.h"
#include "LD.h"
#include "SR.h"
#include "SI.h"
#include "Phases.h"
#include "columns.h"

//function to take a file name from the user and return a path to that file in rsc folder
char *getFilePath(char *input) {
    char *filename = malloc(60);
    sprintf(filename, "rsc/%s", input);
    char *result = strdup(filename);
    free(filename);
    return result;
}
int fileExists(const char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}
/*
int main() {
    Card* deck = loadDeck("rsc/UnShuffledCards.txt");
    int i=0;
    while (i<10) {
        printf("Shuffling deck using SR function\n");
        deck = SR(deck);
        i++;
    }

    printf(displayDynamicInterface(deck));
    freeDeck(deck);
    exit(0);
}
*/
int main() {
    int len;
    Card *deck = NULL;
    Card *head = NULL;
    Column **columns = NULL;

    char command[50] = "";
    char lastCommand[50] = "";
    char argument[50] = "";
    char *message = "Enter a command to start the game";
    char function[9] = " ";
    board();
    char*filename = "";

    while (1) {
        strcpy(lastCommand, handleInput(message, command));
        strcpy(command, lastCommand);
        // Extract function name and argument
        sscanf(command, "%s %s", function, argument);

        function[strlen(function)] = '\0';


        //LD function
        if (strcmp(function, "LD") == 0) {
            // strcpy(lastCommand, "LD");
            char *filePath;
            if (strcmp(argument, "") == 0) { filePath = "rsc/UnShuffledCards.txt"; }
            else { filePath = getFilePath(argument); }
            if (fileExists(filePath) == 1) {
                Card *newDeck = loadDeck(filePath);

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
                    message = "Error: Deck is invalid.";
                }
            } else {
                message = "Error: File not found.";
            }
        }

                //QQ function
            else if (strcmp(function, "QQ") == 0) {
                //  saveDeck(head, "rsc/savedcards.txt");

                freeDeck(deck);
                printf("The program exits.");
                exit(0);

            }
                //P function

            else if (strcmp(function, "P") == 0) {
                if (deck != NULL) {
                    columns = dealCards(head); // Deal cards from the deck into columns
                    message = "OK";
                    //  playPhase(&head); // Enter into the play phase
                } else {
                    message = "Error: No deck loaded.";
                }
            }

                //Move cards from one column to column
            else if (function[0] == 'C' &&
                     function[2] == ':' &&
                     function[5] == '-' &&
                     function[6] == '>' &&
                     function[7] == 'C') {
                int sourceColumn = convertValue(function[1]);;
                char sourceValue = function[3];
                char sourceSuit = function[4];
                int destColumn = convertValue(function[8]);

                moveCard(&columns[sourceColumn - 1], &columns[destColumn - 1], sourceValue, sourceSuit);
                dealColumns(columns);

            }


    //Move from column to foundation
        else if ( function[0]=='C' &&
                  function[2]==':' &&
                  function[5]=='-' &&
                  function[6]=='>' &&
                  function[7]=='F')
        {
            int sourceColumn=convertValue(function[1]);;
            char sourceValue=function[3];
            char sourceSuit=function[4];
            int destColumn=convertValue(function[8]);

            moveCardToFoundation(&columns[sourceColumn-1], &columns[destColumn+6], sourceValue, sourceSuit);
            dealColumns(columns);
        }
    //Move from foundation to column
        else if ( function[0]=='F' &&
                  function[2]==':' &&
                  function[5]=='-' &&
                  function[6]=='>' &&
                  function[7]=='C')
        {
            int sourceColumn=convertValue(function[1]);;
            char sourceValue=function[3];
            char sourceSuit=function[4];
            int destColumn=convertValue(function[8]);

            moveCardFromFoundation(&columns[sourceColumn+6], &columns[destColumn-1], sourceValue, sourceSuit);
            dealColumns(columns);
        }
        else if((strcmp(function, "PR") == 0)){ printColumns(columns);}

                //SR function
            else if (strcmp(function, "SR") == 0) {
                Card *newDeck = SR(head);
                if (newDeck != NULL) {
                    deck = newDeck;
                    head = deck;
                    loadedDeck();
                    message = "OK";
                } else {
                    board();
                    message = "Error: No deck loaded.";
                }
            }
                //SI function
            else if (strcmp(function, "SI") == 0) {
                int input;
                sscanf(argument, "%d", &input);
                Card *newDeck = splitShuffle(head, input);
                if (newDeck != NULL) {
                    deck = newDeck;
                    head = deck;
                    //head = newDeck;
                    loadedDeck();
                    message = "OK";
                } else {
                    board();
                    message = "Error: No deck loaded.";
                }

            }
                //SD function
            else if (strcmp(function, "SD") == 0) {
            char *filePath;
            if (strcmp(argument, "") == 0) { filePath = "rsc/cards.txt"; }
            else { filePath = getFilePath(argument); }
                    saveDeck(head, filePath);
                    message = "OK";
            }
                //SW function
            else if (strcmp(function, "SW") == 0) {
                message = displayDynamicInterface(head);

            }

                //"Unknown command" message
            else {
                strcpy(lastCommand, command);
                message = "Unknown command.";
            }
            strcpy(argument, "");
        }

    }

