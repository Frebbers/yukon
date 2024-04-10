
#ifndef YUKON_CARDDECK_H
#define YUKON_CARDDECK_H

#include <stdio.h>

typedef struct Card {
    char suit;
    char value;
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
Card* createCard(char value, char suit);
Card* pushPosition(Card* head, int position, char value, char suit);

        Card* newCard(int suit, const char *value, int isFaceUp, Card* next, Card* prev);
void freeDeck(Card* head);



#endif //YUKON_CARDDECK_H
