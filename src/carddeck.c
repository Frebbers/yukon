
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

void appendCard(Card** head_ref, char value, char suit) {
    Card *newCard = createCard(value, suit);
    Card *last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = newCard;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newCard;
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
void saveDeck(Card* head, const char *filename) {
    char full[_MAX_PATH];
    _fullpath(full,filename , _MAX_PATH);
    FILE *fp = fopen(full, "w");
    if (fp == NULL) {
        printf("Error: Could not save deck. Invalid path\n");
        }
    else {
        while (head != NULL) {
            fprintf(fp, "%c%c\n", head->value, head->suit);
            head = head->next;
        }
        fclose(fp);
        printf("Deck saved to %s\n", filename);
    }

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

void swapTwoCards (Card* card1, Card* card2){
    char tempSuit = card1->suit;
    char tempValue = card1->value;
    card1->suit = card2->suit;
    card1->value = card2->value;
    card2->suit = tempSuit;
    card2->value = tempValue;
}
