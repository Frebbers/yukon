
#ifndef YUKON_CARDDECK_H
#define YUKON_CARDDECK_H

#include <stdio.h>

typedef struct Card {
    int suit;
    char value[3];
    int isFaceUp;
    struct Card* next;
    struct Card* prev;
} Card;

typedef struct Deck {
    Card* head;
    Card* tail;
    int size;
} Deck;

void addCard(Deck* deck, Card* card);
Card* removeCard(Deck* deck);
Card* createCard(const char *value);
Card* loadDeck(const char *filename);
Card* newCard(int suit, const char *value, int isFaceUp, Card* next, Card* prev);



#endif //YUKON_CARDDECK_H
