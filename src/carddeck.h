
#ifndef YUKON_CARDDECK_H
#define YUKON_CARDDECK_H

#include <stdio.h>
#include <SDL.h>
#include "SDL_render.h"

typedef struct Card {
    char suit;
    char value;
    int isFaceUp;
    struct Card* next;
    SDL_Texture* texture;
} Card;

typedef struct Deck {
    Card* head;
    Card* tail;
    int size;
} Deck;

typedef struct Column {
    Card* head;

    struct Column* next;
} Column;

void createColumn(Column** headColumn, Card card);
Card* createCard(char value, char suit);
void appendCard(Card** head_ref, char value, char suit);
Card* newCard(int suit, const char *value, int isFaceUp, Card* next);
void freeDeck(Card* head);
void saveDeck(Card* head, const char *filename);

int convertValue(char value);
char convertSuit(char suit);
Column** dealCards(Card* card);
void freeColumns(Column** columns, int size);
void printColumns(Column** columns);
void moveCard(Column** sourceColumn, Column** destColumn, char value, char suit);
Card* reverseDealCards(Column** columns);
Column** dealColumns(Column** columns);
#endif //YUKON_CARDDECK_H
