//
// Created by khaik on 04-05-2024.
//

#ifndef UNTITLED_COLUMNS_H
#define UNTITLED_COLUMNS_H
#include "carddeck.h"

typedef struct Column {
    Card* card;

    struct Column* next;
} Column;


char convertSuit(char suit);
int convertValue(char value);
void createColumn(Column** headColumn, Card card);


Column** dealCards(Card* card);
Card* reverseDealCards(Column** columns);


void printColumns(Column** columns);
void moveCard(Column** sourceColumn, Column** destColumn, char value, char suit);
Column** dealColumns(Column** columns);
void moveCardToFoundation(Column** sourceColumn, Column** foundation, char value, char suit);


#endif //UNTITLED_COLUMNS_H
