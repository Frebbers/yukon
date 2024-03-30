
#include "carddeck.h"
#include "stdlib.h"

Card* newCard(int suit, int value, int isFaceUp, Card* next, Card* prev) {
    Card* card = (Card*)malloc(sizeof(Card));
    card->suit = suit;
    card->value = value;
    card->isFaceUp = isFaceUp;
    card->next = next;
    card->prev = prev;
    return card;
}
void addCard(Deck* deck, Card* card) {
    if (deck->head == NULL) {
        deck->head = card;
        deck->tail = card;
    } else {
        deck->tail->next = card;
        card->prev = deck->tail;
        deck->tail = card;
    }
    deck->size++;
}

Card* removeCard(Deck* deck) {
    if (deck->head == NULL) {
        return NULL;
    }
    Card* card = deck->head;
    deck->head = deck->head->next;
    if (deck->head != NULL) {
        deck->head->prev = NULL;
    } else {
        deck->tail = NULL;
    }
    deck->size--;
    return card;
}