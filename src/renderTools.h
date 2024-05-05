//
// Created by frede on 27-04-2024.
//

#include "carddeck.h"

#ifndef UNTITLED_RENDERTOOLS_H
#define UNTITLED_RENDERTOOLS_H

#endif //UNTITLED_RENDERTOOLS_H
SDL_Texture* loadTexture(const char* filepath, SDL_Renderer* renderer);
void applyCardTexture(SDL_Renderer* renderer, Card* card);
void closeSDL(SDL_Window* window, SDL_Renderer* renderer);
SDL_Window *createWindow(int WINDOW_WIDTH, int WINDOW_HEIGHT);
SDL_Renderer* initSDL(SDL_Window* window);
/**
 * Renders the game board
 * @param renderer The renderer to render the game board to
 * @param backgroundTexture The texture of the background
 * @param columnSpaces The SDL_Rect array of the column spaces
 * @param foundationSpaces The SDL_Rect array of the foundation spaces
 */
void renderGameBoard(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Rect* columnSpaces, SDL_Rect* foundationSpaces);
/**
 * Renders a column of cards
 * @param renderer The renderer to render the cards to
 * @param head The head of the column
 * @param x The x position of the column
 * @param y The y position of the column
 * @param compressionFactor The distance between the top of one card and the next. 0 = no compression, 65 = cards will be rendered directly on top of each other

 */
void renderColumn(SDL_Renderer* renderer, Card* head, int x, int y, int compressionFactor);