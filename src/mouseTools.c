//
// Created by frede on 05-05-2024.
//

#include "mouseTools.h"
#include "SDL.h"
#include "columns.h"
#include "renderTools.h"
char* dropCardStack(Card* stack, Column* columns, Column* foundations, int x, int y) {
    // Determine if the drop is over a column or foundation
    for (int i = 0; i < 7; i++) {
        SDL_Rect columnRect = {columns[i].x, columns[i].y, COLUMN_WIDTH, COLUMN_HEIGHT};
        if (x >= columnRect.x && x < (columnRect.x + COLUMN_WIDTH) &&
            y >= columnRect.y && y < (columnRect.y + COLUMN_HEIGHT)) {
            // Drop over a column
            return moveCard(&(columns[i]), &stack, stack->value, stack->suit);
        }
    }
    for (int j = 0; j < 4; j++) {
        SDL_Rect foundationRect = {foundations[j].card->rect.x, foundations[j].card->rect.y, FOUNDATION_WIDTH, FOUNDATION_HEIGHT};
        if (x >= foundationRect.x && x < (foundationRect.x + FOUNDATION_WIDTH) &&
            y >= foundationRect.y && y < (foundationRect.y + FOUNDATION_HEIGHT)) {
            // Drop over a foundation
            return moveCardToFoundation(&stack, &(foundations[j]), stack->value, stack->suit);
        }
    }
    return "Error!_Invalid drop location";
}
void handleMouseEvents(SDL_Event* event, Column* columns, Column* foundations, Card** draggedCard, SDL_Point* originalPosition, int* isDragging) {
    static Card* draggedCardStack = NULL;
    static SDL_Point dragOffset;

    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                draggedCardStack = getCardStackAtPosition(columns, event->button.x, event->button.y);
                if (draggedCardStack) {
                    *originalPosition = (SDL_Point){draggedCardStack->rect.x, draggedCardStack->rect.y};
                    dragOffset.x = event->button.x - draggedCardStack->rect.x;
                    dragOffset.y = event->button.y - draggedCardStack->rect.y;
                    *draggedCard = draggedCardStack;
                    *isDragging = 1;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (*isDragging && event->button.button == SDL_BUTTON_LEFT) {
                int dropX = event->button.x - dragOffset.x;
                int dropY = event->button.y - dragOffset.y;
                char* result = dropCardStack(draggedCardStack, columns, numColumns, foundations, 4, dropX, dropY);
                if (strcmp(result, "OK") != 0) {
                    // Reset position if drop is not valid
                    draggedCardStack->rect.x = originalPosition->x;
                    draggedCardStack->rect.y = originalPosition->y;
                }
                *isDragging = 0;
                draggedCardStack = NULL;
            }
            break;
        case SDL_MOUSEMOTION:
            if (*isDragging) {
                draggedCardStack->rect.x = event->motion.x - dragOffset.x;
                draggedCardStack->rect.y = event->motion.y - dragOffset.y;
                moveCardStack(draggedCardStack->next, event->motion.x - dragOffset.x, event->motion.y - dragOffset.y - draggedCardStack->rect.y);
            }
            break;
    }
}

/**
 * Moves a stack of cards at the given position.
 * @param stack The card stack to drop
 * @param x The x position to drop the card stack
 * @param y The y position to drop the card stack
 * @return 1 if the drop was successful, 0 otherwise
 */
void moveCardStack(Card* stack, int deltaX, int deltaY) {
    while (stack != NULL) {
        stack->rect.x += deltaX;
        stack->rect.y += deltaY;
        stack = stack->next;
    }
}



