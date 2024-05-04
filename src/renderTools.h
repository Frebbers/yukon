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