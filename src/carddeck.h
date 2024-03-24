//
// Created by Magnus on 24/03/2024.
//

#ifndef YUKON_CARDDECK_H
#define YUKON_CARDDECK_H

#include <stdio.h>

typedef struct Card {
    int suit;
    int value;
    int isFaceUp;
    struct Card* next;
    struct Card* prev;
} Card;

typedef struct Deck {
    Card* head;
    Card* tail;
    int size;
} Deck;




#endif //YUKON_CARDDECK_H
