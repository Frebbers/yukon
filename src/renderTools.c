//
// Created by frede on 27-04-2024.
//
#include <SDL.h>
#include <stdio.h>
#include <renderTools.h>
#include <SDL_image.h>
#include "carddeck.h"
#include "columns.h"



//Cleans up the SDL window and renderer. Must be called before the program ends
void closeSDL(SDL_Window* window, SDL_Renderer* renderer) {
    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window *createWindow(int WINDOW_WIDTH, int WINDOW_HEIGHT) {
    // Create window
    SDL_Window *window = SDL_CreateWindow("Yukon Solitaire", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return NULL;
    }
    return window;
}
//initializes the SDL renderer
SDL_Renderer* initSDL(SDL_Window* window) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return 0;
    }

    // Check if window was created
    if (window == NULL) {
        printf("createWindow() was called but 'window' is NULL: %s\n", SDL_GetError());
        return 0;
    }
    // Create renderer
    SDL_Renderer *newRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
    if (newRenderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 0;
    }
    return newRenderer;
}

SDL_Texture* loadTexture(const char* filepath, SDL_Renderer* renderer) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(filepath);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", filepath, IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", filepath, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void applyCardBackTexture(SDL_Renderer* renderer, Card* card) {
    char pathToCard[] = "";
    sprintf(pathToCard,"rsc/graphics/cardBack.png");
    card->texture = loadTexture(pathToCard, renderer);
}
//renders the back of the card if it is facedown, otherwise it renders the front of the card
void applyCardTexture(SDL_Renderer* renderer, Card* card) {
    if (!card->isFaceUp) {applyCardBackTexture(renderer, card);
    }
    else {char pathToCard[100];
        sprintf(pathToCard,"rsc/graphics/%c%c.png",card->value,card->suit);
        card->texture = loadTexture(pathToCard, renderer);}
}
void renderCard(SDL_Renderer* renderer, Card* card, int x, int y) {
    SDL_Rect srcRect = {0, 0, ORIGINAL_CARD_WIDTH, ORIGINAL_CARD_HEIGHT}; // Source rectangle
    SDL_Rect dstRect = {x, y, SCALED_CARD_WIDTH, SCALED_CARD_HEIGHT};     // Destination rectangle scaled
    card->rect = dstRect;
    SDL_RenderCopy(renderer, card->texture, &srcRect, &dstRect);
}


void renderColumn(SDL_Renderer* renderer, Card* head, int x, int y, int distanceBetweenCards) {

    while (head != NULL) {
        renderCard(renderer, head, x, y);
        head = head->next;
        y += distanceBetweenCards;
    }
    SDL_RenderPresent(renderer);
}
void renderGameBoard(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Rect* columnSpaces, SDL_Rect* foundationSpaces, Column* columns) {
    // Render the background first
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    Column* tempColumn = columns;
    // Render column spaces (for columns)
    for (int i = 0; i < 7; i++) {
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); // Light grey
        SDL_RenderFillRect(renderer, &columnSpaces[i]);
       if (columns != NULL) {
           columns->rect = columnSpaces[i];
           columns = columns->next;
       }
    }

    // Render foundation spaces (for foundations)
    for (int i = 0; i < 4; i++) {
        SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255); // Slightly darker grey
        SDL_RenderFillRect(renderer, &foundationSpaces[i]);
        if (columns != NULL) {
            columns->rect = foundationSpaces[i + 7];
            columns = columns->next;
        }
    }
    columns = tempColumn;
}

void setupRects(SDL_Rect* columnSpaces, SDL_Rect* foundationSpaces) {
    // Set up columns
    for (int i = 0; i < 7; i++) {
        columnSpaces[i].x = COLUMN_PADDING + i * (COLUMN_WIDTH + COLUMN_PADDING);
        columnSpaces[i].y = COLUMN_PADDING;  // Top padding
        columnSpaces[i].w = COLUMN_WIDTH;
        columnSpaces[i].h = COLUMN_HEIGHT;
        if (i == 6) {
            for (int j = 0; j < 4; j++) {
                foundationSpaces[j].x = 7 * (COLUMN_WIDTH + COLUMN_PADDING) + COLUMN_TO_FOUNDATION_PADDING;
                foundationSpaces[j].y = COLUMN_PADDING + j * (FOUNDATION_HEIGHT + FOUNDATION_PADDING);
                foundationSpaces[j].w = FOUNDATION_WIDTH;
                foundationSpaces[j].h = FOUNDATION_HEIGHT;
            }
        }
    }
}
Column* getColumnAtPosition(Column* columns, int x, int y) {
    Column* currentColumn = columns;
    int i = 0;
    while (currentColumn != NULL) {
        SDL_Rect columnRect = {currentColumn->rect.x, currentColumn->rect.y, COLUMN_WIDTH, WINDOW_HEIGHT};
        if (x >= columnRect.x && x < (columnRect.x + COLUMN_WIDTH)) {
            if (i < 7) {
                return currentColumn;
            }
            else {
                // Check which foundation is at the position
                if (y >= columnRect.y && y < (columnRect.x + COLUMN_HEIGHT)) {
                    return currentColumn;
                }
            }
        }
        i++;
        currentColumn = currentColumn->next;
    }
    return currentColumn;
}

Card* getCardStackAtPosition(Column* column, int y) {
    Card* card = column->card;
    while (card != NULL) {
        SDL_Rect cardRect = {card->rect.x, card->rect.y, SCALED_CARD_WIDTH, SCALED_CARD_HEIGHT};
        if (y >= cardRect.y && y < (cardRect.y + 60)) {
            return card; // Return the first card in the stack at the cursor position
        }
        card = card->next;
    }
    return NULL; // No card found at this position
}

void renderColumns(SDL_Renderer* renderer, Column* columns, SDL_Rect* columnSpaces) {
    Column* currentColumn = columns;
    int distanceBetweenCards = 60;
    int i = 0;
    while (currentColumn != NULL) {
       // if (i == 7){distanceBetweenCards = 0;}
        renderColumn(renderer, currentColumn->card, columnSpaces[i].x, columnSpaces[i].y, distanceBetweenCards);
        SDL_Rect columnRect = {columnSpaces[i].x, columnSpaces[i].y, COLUMN_WIDTH, WINDOW_HEIGHT};
        currentColumn -> rect = columnRect;
        currentColumn = currentColumn->next;
        i++;
    }
}




