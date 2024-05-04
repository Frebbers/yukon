//
// Created by frede on 27-04-2024.
//
#include <SDL.h>
#include <stdio.h>
#include <renderTools.h>
#include <SDL_image.h>
#include "carddeck.h"
const double SCALE_FACTOR = 0.35;
const int ORIGINAL_CARD_WIDTH = 500;
const int ORIGINAL_CARD_HEIGHT = 726;
const int SCALED_CARD_WIDTH = (int)(ORIGINAL_CARD_WIDTH * SCALE_FACTOR);
const int SCALED_CARD_HEIGHT = (int)(ORIGINAL_CARD_HEIGHT * SCALE_FACTOR);

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
