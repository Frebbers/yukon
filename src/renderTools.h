//
// Created by frede on 27-04-2024.
//

#include "carddeck.h"
#include "columns.h"

#ifndef UNTITLED_RENDERTOOLS_H
#define UNTITLED_RENDERTOOLS_H

#endif //UNTITLED_RENDERTOOLS_H
extern const double CARD_SCALE_FACTOR;
extern const int ORIGINAL_CARD_WIDTH;
extern const int ORIGINAL_CARD_HEIGHT;
extern const int SCALED_CARD_WIDTH;
extern const int SCALED_CARD_HEIGHT;
extern const int COLUMN_WIDTH;
extern const int COLUMN_HEIGHT;
extern const int COLUMN_PADDING;
extern const int FOUNDATION_WIDTH;
extern const int FOUNDATION_HEIGHT;
extern const int FOUNDATION_PADDING;
extern const int COLUMN_TO_FOUNDATION_PADDING;
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

/**
 * Loads a texture from a file and returns it
 * @param filepath The path to the file from the binary root
 * @param renderer The renderer to load the texture to
 * @return The texture loaded from the file
 * @author Frederik Bode Hendrichsen s224804
 */
SDL_Texture* loadTexture(const char* filepath, SDL_Renderer* renderer);
void applyCardTexture(SDL_Renderer* renderer, Card* card);
/**
 * Closes the SDL window and renderer and cleans up the memory
 * @param window The window to close
 * @param renderer The renderer to close
 * @author Frederik Bode Hendrichsen s224804
 */
void closeSDL(SDL_Window* window, SDL_Renderer* renderer);
SDL_Window *createWindow(int WINDOW_WIDTH, int WINDOW_HEIGHT);
/**
 * Initializes the SDL renderer
 * @param window The window to create the renderer for
 * @return The renderer created or NULL if an error occurred
 * @author Frederik Bode Hendrichsen s224804
 */
SDL_Renderer* initSDL(SDL_Window* window);
void setupRects(SDL_Rect* columnSpaces, SDL_Rect* foundationSpaces);
/**
 * Renders the game board
 * @param renderer The renderer to render the game board to
 * @param backgroundTexture The texture of the background
 * @param columnSpaces The SDL_Rect array of the column spaces
 * @param foundationSpaces The SDL_Rect array of the foundation spaces
 * @author Frederik Bode Hendrichsen s224804
 */
void renderGameBoard(SDL_Renderer* renderer, SDL_Texture* backgroundTexture, SDL_Rect* columnSpaces, SDL_Rect* foundationSpaces, Column* columns);
/**
 * Renders a column of cards to the screen
 * @param renderer The renderer to render to
 * @param head The head of the linked list of cards
 * @param x The x-coordinate to render the first card
 * @param y The y-coordinate to render the first card
 * @param distanceBetweenCards The distance between each card - default is 65
 * @author Frederik Bode Hendrichsen s224804
 */
void renderColumn(SDL_Renderer* renderer, Card* head, int x, int y, int distanceBetweenCards);
/**
 * Returns the card at the position x, y
 * @param columns The column to search for a card
 * @param y The y-coordinate to search
 * @author Frederik Bode Hendrichsen s224804
 */

/**
 * Moves a stack of cards at the given position.
 * @param renderer The renderer to render the columns
 * @param columns The columns to render
 * @param columnSpaces The SDL_Rect array of the column origin spaces
 * @author
 */
void renderColumns(SDL_Renderer* renderer, Column* columns, SDL_Rect* columnSpaces);
Card* getCardStackAtPosition(Column* column, int y);
/**
 * Returns the column at the position x
 * @param columns The columns to search for the column
 * @param x The x-coordinate to search
 * @return The column at the position x
 * @author Frederik Bode Hendrichsen s224804
 */
Column* getColumnAtPosition(Column* columns, int x, int y);