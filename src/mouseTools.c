//
// Created by frede on 05-05-2024.
//

#include "mouseTools.h"
#include "SDL.h"
#include "columns.h"

void handleMouseEvents(SDL_Event* event, Column* columns, Card** draggedCardStack, SDL_Point* originalPosition, int* isDragging) {
    switch (event->type) {
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                *draggedCardStack = getCardStackAtPosition(columns, event->button.x, event->button.y);
                if (*draggedCardStack) {
                    *originalPosition = (SDL_Point){(*draggedCardStack)->x, (*draggedCardStack)->y};
                    *isDragging = 1;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (*isDragging && event->button.button == SDL_BUTTON_LEFT) {
                if (!dropCardStack(*draggedCardStack, columns, event->button.x, event->button.y)) {
                    // Reset position if drop is not valid
                    (*draggedCardStack)->x = originalPosition->x;
                    (*draggedCardStack)->y = originalPosition->y;
                }
                *isDragging = 0;
            }
            break;
        case SDL_MOUSEMOTION:
            if (*isDragging) {
                moveCardStack(*draggedCardStack, event->motion.x, event->motion.y);
            }
            break;
    }
}
