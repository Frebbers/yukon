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
#include "renderTools.h"
#include "columns.h"
#include "mouseTools.h"
const double CARD_SCALE_FACTOR = 0.32;
const int ORIGINAL_CARD_WIDTH = 500;
const int ORIGINAL_CARD_HEIGHT = 726;
const int SCALED_CARD_WIDTH = (int)(ORIGINAL_CARD_WIDTH * CARD_SCALE_FACTOR);
const int SCALED_CARD_HEIGHT = (int)(ORIGINAL_CARD_HEIGHT * CARD_SCALE_FACTOR);
const int COLUMN_WIDTH = SCALED_CARD_WIDTH;
const int COLUMN_HEIGHT = SCALED_CARD_HEIGHT;
const int COLUMN_PADDING = 25;
const int FOUNDATION_WIDTH = SCALED_CARD_WIDTH;
const int FOUNDATION_HEIGHT = SCALED_CARD_HEIGHT;
const int FOUNDATION_PADDING = 11;
const int COLUMN_TO_FOUNDATION_PADDING = COLUMN_PADDING*3;
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 1080;

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

int main(int argc, char *argv[]) {
    int FPS = 60;
    int SCROLL_SPEED = 5;
    SDL_INIT_EVERYTHING;
    SDL_Window *window = createWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!window) {return 1;}
    SDL_Renderer *rend = initSDL(window);
    if (!rend) {
        SDL_DestroyWindow(window);
        return 1;}
    //Create the rects for the column and foundation spaces
    SDL_Rect columnSpaces[7];
    SDL_Rect foundationSpaces[4];
    SDL_Texture *backGroundTexture = loadTexture("rsc/graphics/background_basic.png", rend);
    setupRects(columnSpaces, foundationSpaces);
   // renderGameBoard(rend, loadTexture("rsc/graphics/background_basic.png", rend), columnSpaces, foundationSpaces,);
    // Load image into memory
    Card* deck = loadDeck("rsc/UnShuffledCards.txt", rend);
    if (deck == NULL) {
        printf("Could not load deck: %s\n", SDL_GetError());
        closeSDL(window, rend);
        return 1;
    }
/*   Card* temp = deck;
    for (int i = 0; i < 7; i++) {
        deck = deck->next;
    }
    deck->next = NULL;
    deck = temp;
   // SDL_RenderClear(rend);
    //renderColumn(rend, deck, 0, 0, 0);
*/
/*
    //create texture from surface
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if (!tex) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return 1;
    }
    // Get the dimensions of texture and set destination to the whole screen
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    // Center the texture on the screen
    dest.x = (WINDOW_WIDTH - dest.w) / 2;
    dest.y = (WINDOW_HEIGHT - dest.h) / 2;
    float y_pos = WINDOW_HEIGHT;



*/
    Column **columns = columnFront(deck);
    dealColumns(columns);
    int close_requested = 0;
    SDL_Event windowEvent;
// Initialize dragging state
    int isDragging = 0;
    Card* draggedCard = NULL;
    renderGameBoard(rend, backGroundTexture, columnSpaces, foundationSpaces, *columns);
    while (!close_requested) {
        while (SDL_PollEvent(&windowEvent)) {
            // Handle mouse events with updated function call
            handleMouseEvents(&windowEvent, *columns, &isDragging, &draggedCard);

            if (windowEvent.type == SDL_QUIT) {
                close_requested = 1;
            }
        }

        // Clear the renderer
        //SDL_RenderClear(rend);

        // Render the game board and the columns
        //renderGameBoard(rend, backGroundTexture, columnSpaces, foundationSpaces, *columns);
        renderColumns(rend, *columns, columnSpaces);

        // Render dragged card last so it appears on top
        if (isDragging && draggedCard != NULL) {
            renderCard(rend, draggedCard, windowEvent.button.x - draggedCard->rect.w / 2,
                        windowEvent.button.y - draggedCard->rect.h / 2);
        }

        // Update the screen
        SDL_RenderPresent(rend);

        // Cap the frame rate
        SDL_Delay(1000 / FPS);
        //SDL_RenderClear(rend);
    }


    freeDeck(deck);
    closeSDL(window, rend);
    return 0;
}
/*
    int startGame = 1;
    int len;
   // Card *deck = NULL;
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
                Card *newDeck = loadDeck(filePath, rend);

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
                closeSDL(window, rend);
                exit(0);

            }
                //P function

        else if (strcmp(function, "P") == 0) {
            if (deck != NULL) {
                columns = dealCards(head); // Deal cards from the deck into columns
                message = "OK";
                int inPlayPhase = 1;
                while (inPlayPhase) {
                    memset(command, 0, sizeof(command));
                    memset(argument, 0, sizeof(argument));
                    memset(function, 0, sizeof(function));

                    printf("In Play: %s\nINPUT >", message);
                    fgets(command, sizeof(command), stdin);
                    sscanf(command, "%s %s", function, argument);

                    if (strcmp(function, "Q") == 0) {
                        printf("Ending play phase.\n");
                        inPlayPhase = 0; // Properly end play phase
                        } else if (function[0] == 'C' &&
                                 function[2] == ':' &&
                                 function[5] == '-' &&
                                 function[6] == '>' &&
                                 function[7] == 'C') {
                            int sourceColumn = convertValue(function[1]);;
                            char sourceValue = function[3];
                            char sourceSuit = function[4];
                            int destColumn = convertValue(function[8]);

                            message=moveCard(&columns[sourceColumn - 1], &columns[destColumn - 1], sourceValue, sourceSuit);
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

                            message=moveCardToFoundation(&columns[sourceColumn-1], &columns[destColumn+6], sourceValue, sourceSuit);
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

                            message=moveCardFromFoundation(&columns[sourceColumn+6], &columns[destColumn-1], sourceValue, sourceSuit);
                            dealColumns(columns);
                        }
                        else if((strcmp(function, "PR") == 0)){ printColumns(columns);}

                    }
                } else {
                    message = "Error: No deck loaded.";
                }
            }

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

*/