
#include "carddeck.h"
#include "stdlib.h"
#include "string.h"
#include "rendertools.h"
#include <SDL_image.h>


Card* createCard(char value, char suit) {
    Card* newCard = (Card*)malloc(sizeof(Card));
    if (newCard == NULL) {
        printf("Error: Unable to allocate memory for new card.\n");
        return NULL;
    }
    newCard->suit = suit;
    newCard->value = value;
    newCard->isFaceUp = 0;

    return newCard;
}

void appendCard(Card** head_ref, char value, char suit) {
    Card *newCard = createCard(value, suit);
    Card *last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = newCard;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newCard;
}

void saveDeck(Card* head, const char *filename) {
    char full[_MAX_PATH];
    _fullpath(full,filename , _MAX_PATH);
    FILE *fp = fopen(full, "w");
    if (fp == NULL) {
        printf("Error: Could not save deck. Invalid path\n");
        }
    else {
        while (head != NULL) {
            fprintf(fp, "%c%c\n", head->value, head->suit);
            head = head->next;
        }
        fclose(fp);
        printf("Deck saved to %s\n", filename);
    }

}

//Befrier memory
void freeDeck(Card* head) {
    Card* tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}








