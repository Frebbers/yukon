//
// Created by frede on 27-04-2024.
//
#include <SDL.h>
#include <stdio.h>
#include <renderTools.h>
#include <SDL_image.h>
#include "carddeck.h"
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
int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 1080;

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
void renderCard(SDL_Renderer* renderer, Card card, int x, int y) {
    SDL_Rect srcRect = {0, 0, ORIGINAL_CARD_WIDTH, ORIGINAL_CARD_HEIGHT}; // Source rectangle
    SDL_Rect dstRect = {x, y, SCALED_CARD_WIDTH, SCALED_CARD_HEIGHT};     // Destination rectangle scaled

    SDL_RenderCopy(renderer, card.texture, &srcRect, &dstRect);
}

void renderColumn(SDL_Renderer* renderer, Card* head, int x, int y, int compressionFactor) {

    while (head != NULL) {
        renderCard(renderer, *head, x, y);
        head = head->next;
        y += 65 - compressionFactor;
    }
    SDL_RenderPresent(renderer);
}
void renderGameBoard(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Rect* columnSpaces, SDL_Rect* foundationSpaces) {
    // Render the background first
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

    // Render column spaces (for columns)
    for (int i = 0; i < 7; i++) {
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); // Light grey
        SDL_RenderFillRect(renderer, &columnSpaces[i]);
    }

    // Render foundation spaces (for foundations)
    for (int i = 0; i < 4; i++) {
        SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255); // Slightly darker grey
        SDL_RenderFillRect(renderer, &foundationSpaces[i]);
    }

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


