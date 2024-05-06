//
// Created by frede on 05-05-2024.
//

#include "mouseTools.h"
#include "SDL.h"
#include "columns.h"
#include "renderTools.h"

/**
 * Moves a stack of cards at the given position.
 * @param stack The card stack to drop
 * @param x The x position to render the card stack
 * @param y The y position to render the card stack
 */
void moveCardStack(Card* stack, int deltaX, int deltaY) {
    while (stack != NULL) {
        stack->rect.x += deltaX;
        stack->rect.y += deltaY;
        stack = stack->next;
    }
}
char* dropCardStack(Card* stack, Column* stackColumn, Column* columns, int x, int y) {
    // Determine if the drop is over a column or foundation
    Column *currentColumn = columns;
    int i = 0;
    while (currentColumn != NULL) {
        SDL_Rect columnRect = {currentColumn->rect.x, currentColumn->card->rect.y, COLUMN_WIDTH, WINDOW_HEIGHT};
        if (x >= columnRect.x && x < (columnRect.x + COLUMN_WIDTH) &&
            y >= columnRect.y && y < (columnRect.y + COLUMN_HEIGHT)) {
            // Drop over a column
            if (i < 7) {
                return moveCard(&stackColumn, &currentColumn, stack->value, stack->suit);
            }
        } else {
            Column *foundation = getColumnAtPosition(columns, x, y);
            if (foundation == NULL) {
                return "Error!_No foundation found";
            }
            SDL_Rect foundationRect = {currentColumn->rect.x, currentColumn->card->rect.y,
                                       COLUMN_WIDTH,COLUMN_HEIGHT};
            if (x >= foundationRect.x && x < (foundationRect.x + COLUMN_WIDTH) &&
                y >= foundationRect.y && y < (foundationRect.y + FOUNDATION_HEIGHT)) {
                return moveCardToFoundation(&stackColumn, &foundation, stack->value, stack->suit);
            }

            /* for (int j = 0; j < 4; j++) {
                 SDL_Rect foundationRect = {foundations[j].card->rect.x, foundations[j].card->rect.y, FOUNDATION_WIDTH, FOUNDATION_HEIGHT};
                 if (x >= foundationRect.x && x < (foundationRect.x + FOUNDATION_WIDTH) &&
                     y >= foundationRect.y && y < (foundationRect.y + FOUNDATION_HEIGHT)) {
                     // Drop over a foundation
                     return moveCardToFoundation(&stackColumn, &(foundations[j]), stack->value, stack->suit);
                 }
             } */
        }
        currentColumn = currentColumn->next;
        i++;
    }
    return "Error!_Invalid drop location";
}
    void handleMouseEvents(SDL_Event *event, Column *columns, int *isDragging) {
        Card* draggedCardStack;
        static SDL_Point dragOffset;
        char *result = NULL;
        SDL_Point originalPosition;
        Column* currentColumn;
        switch (event->type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event->button.button == SDL_BUTTON_LEFT) {
                    currentColumn = getColumnAtPosition(columns, event->button.x, event->button.y);
                    draggedCardStack = getCardStackAtPosition(currentColumn, event->button.y);

                    if (draggedCardStack) {
                        originalPosition = (SDL_Point){draggedCardStack->rect.x, draggedCardStack->rect.y};
                        dragOffset.x = event->button.x - draggedCardStack->rect.x;
                        dragOffset.y = event->button.y - draggedCardStack->rect.y;
                        *isDragging = 1;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (*isDragging && event->button.button == SDL_BUTTON_LEFT) {
                    int dropX = event->button.x - dragOffset.x;
                    int dropY = event->button.y - dragOffset.y;
                    if (draggedCardStack == NULL) {
                        result = "Error!_No card stack to drop";
                    } else {
                        result = dropCardStack(draggedCardStack, currentColumn, columns, dropX, dropY);
                    }
                    if (strcmp(result, "OK") != 0) {
                        // Reset position if drop is not valid
                        moveCardStack(draggedCardStack, originalPosition.x - draggedCardStack->rect.x,
                                      originalPosition.y - draggedCardStack->rect.y);
                       // draggedCardStack->rect.x = originalPosition.x;
                       // draggedCardStack->rect.y = originalPosition.y;
                    }
                    *isDragging = 0;
                    draggedCardStack = NULL;
                }
                break;
            case SDL_MOUSEMOTION:
                if (isDragging) {
                    draggedCardStack->rect.x = event->motion.x - dragOffset.x;
                    draggedCardStack->rect.y = event->motion.y - dragOffset.y;
                    moveCardStack(draggedCardStack->next, event->motion.x - dragOffset.x,
                                  event->motion.y - dragOffset.y - draggedCardStack->rect.y);
                }
                break;
        }
    }





