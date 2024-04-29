//
// Created by khaik on 07-04-2024.
//
#include "carddeck.h"
#include "stdlib.h"
#include "string.h"
#include "renderTools.h"

Card* loadDeck(const char *filename, SDL_Renderer *renderer) {
    FILE *file = fopen(filename, "r");
    char *message;
    if (file == NULL) {
       return NULL;
    }

    char buffer[2];
    Card *head = NULL, *tail = NULL;

    while (fscanf(file, "%2s", buffer) == 1) {
        Card *newCard = createCard(buffer[0], buffer[1]);
        newCard -> isFaceUp = 1;
        applyCardTexture(renderer, newCard);
        if (head == NULL) {
            head = newCard;
            tail = newCard;
        } else {
            tail->next = newCard;
            tail = newCard;
            tail -> next = NULL;
        }
    }
    fclose(file);
    //return head;
    return head;
}

#include "LD.h"
