#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SW.h"
#include "carddeck.h"
#include "board.h"
#include "LD.h"
#include "SR.h"
#include "SI.h"
#include "Phases.h"
#include <SDL.h>


int main(int argc, char *argv[]) {
int width = 800;
int height = 600;
    SDL_INIT_EVERYTHING;
    SDL_Window *window = SDL_CreateWindow("Yukon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(window, -1, render_flags);
    if (!rend) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Event windowEvent;
    while(1==1) {
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) {
                break;
            }
        }

    }
    SDL_DestroyWindow(window);
    SDL_Quit();


    int startGame = 1;
    int len;
    Card *deck = NULL;
    Card *head = NULL;
    Column** columns = NULL;

    char command[50] = "";
    char lastCommand[50] = "";
    char argument[50] = "";
    char *message = "Enter a command to start the game";
    char function[9]= " ";
    board();

    while (startGame == 1){
        strcpy(lastCommand, handleInput(message, command));
        strcpy(command, lastCommand);
        // Extract function name and argument
        sscanf(command, "%s %s", function, argument);

        function[strlen(function)] = '\0';


    //LD function
        if (strcmp(function, "LD") == 0){
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
                columns=dealCards(head); // Deal cards from the deck into columns
                 message = "OK";
              //  playPhase(&head); // Enter into the play phase
            } else {
                message = "Error: No deck loaded.";
            }
        }

    //Move cards from one column to column
        else if ( function[0]=='C' &&
                    function[2]==':' &&
                        function[5]=='-' &&
                         function[6]=='>' &&
                          function[7]=='C')
        {
            int sourceColumn=convertValue(function[1]);;
            char sourceValue=function[3];
            char sourceSuit=function[4];
            int destColumn=convertValue(function[8]);

            moveCard(&columns[sourceColumn-1], &columns[destColumn-1], sourceValue, sourceSuit);
            dealColumns(columns);

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
            int input;
            sscanf(argument, "%d", &input);
            Card* newDeck = splitShuffle(head,input);
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

