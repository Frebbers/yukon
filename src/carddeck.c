
#include "carddeck.h"
#include "stdlib.h"
#include "string.h"


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

Card* createCard(char value, char suit) {
    Card* newCard = (Card*)malloc(sizeof(Card));
    if (newCard == NULL) {
        printf("Error: Unable to allocate memory for new card.\n");
        return NULL;
    }
    newCard->suit = suit;
    newCard->value = value;
    newCard->isFaceUp = 0;
    newCard->next = NULL;
    newCard->prev = NULL;
    return newCard;
}

Card* pushPosition(Card* head, int position, char value, char suit) {

    Card *tail = head;
    Card* newCard = (Card*)malloc(sizeof(Card));

    newCard->suit = suit;
    newCard->value = value;
    newCard->isFaceUp = 0;
    newCard->next = NULL;
    newCard->prev = NULL;

    int counter = 0;

    while(counter < (position-1)){
        tail = tail->next;
        counter++;
    }

    newCard->next = tail->next;
    tail->next = newCard;
    return newCard;

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
