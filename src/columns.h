//
// Created by khaik on 04-05-2024.
//

#ifndef UNTITLED_COLUMNS_H
#define UNTITLED_COLUMNS_H
#include "carddeck.h"

typedef struct Column {
    Card* card;
    SDL_Rect rect;
    struct Column* next;

} Column;
Column** columnFront(Card* card);
int convertValue(char value);
void createColumn(Column** headColumn, Card card);
Column** dealCards(Card* card);
Card* reverseDealCards(Column** columns);
void printColumns(Column** columns);
char* moveCard(Column** sourceColumn, Column** destColumn, char value, char suit);
Column** dealColumns(Column** columns);
char* moveCardToFoundation(Column** sourceColumn, Column** foundation, char value, char suit);
char* moveCardFromFoundation(Column** foundation, Column** destColumn, char value, char suit);
Column** columnFront(Card* card);
Column** dealColumnsFront(Card* card);

#endif //UNTITLED_COLUMNS_H
