
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

typedef struct Column {
    Card* card;

    struct Column* next;
} Column;

void createColumn(Column** headColumn, Card card);
Column** makeC(Card* card);
void addCard(Deck* deck, Card* card);
Card* removeCard(Deck* deck);
Card* createCard(char value, char suit);
Card* pushPosition(Card* head, int position, char value, char suit);
void appendCard(Card** head_ref, char value, char suit);
        Card* newCard(int suit, const char *value, int isFaceUp, Card* next, Card* prev);
void freeDeck(Card* head);
void saveDeck(Card* head, const char *filename);

int convertValue(char value);
char convertSuit(char suit);
Column** dealCards(Card* card);
void freeColumns(Column** columns, int size);
void printColumns(Column** columns);
void findAndPrintCardInColumn(Column* column, char value, char suit);
void moveCard(Column** sourceColumn, Column** destColumn, char value, char suit);
#endif //YUKON_CARDDECK_H
