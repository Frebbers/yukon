
#include "carddeck.h"
#include "stdlib.h"
#include "string.h"

Card* newCard(int suit, const char *value, int isFaceUp, Card* next, Card* prev) {
    Card* card = (Card*)malloc(sizeof(Card));
    if (card != NULL){
        card->suit = suit;
        strcpy(card->value, value);
        card->isFaceUp = isFaceUp;
        card->next = next;
        card->prev = prev;
    }

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

Card* createCard(const char *value) {
    Card *newCard = (Card *)malloc(sizeof(Card));
    if (newCard) {
        strcpy(newCard->value, value);
        newCard->next = NULL;
    }
    return newCard;
}


Card* loadDeck(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: No deck loaded.\n");
        return NULL;
    }

    char buffer[3];
    Card *head = NULL, *tail = NULL;

    while (fscanf(file, "%2s", buffer) == 1) {
        Card *newCard = createCard(buffer);
        if (head == NULL) {
            head = newCard;
            tail = newCard;
        } else {
            tail->next = newCard;
            tail = newCard;
        }
    }

    fclose(file);
    return head;
}
void saveDeck(Card* head, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not save deck. Invalid path\n");
        }
    else {
        while (head != NULL) {
            fprintf(fp, "%s\n", head->value);
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
