
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

Card* newCard(int suit, int value, int isFaceUp, Card* next, Card* prev);




#endif //YUKON_CARDDECK_H
