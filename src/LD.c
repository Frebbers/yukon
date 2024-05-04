//
// Created by khaik on 07-04-2024.
//
#include "carddeck.h"
#include "stdlib.h"
#include "string.h"
#include "renderTools.h"
//turns a card string into an integer
int card_to_int(char card[2]) {
    char ranks[] = "A23456789TJQK";
    char suits[] = "CDHS";
    int rank = 0;
    int suit = 0;

    // Find the rank index
    while (ranks[rank] != card[0]) {
        rank++;
        if (rank == 13) {return -1;}
    }

    // Find the suit index
    while (suits[suit] != card[1]) {
        suit++;
        if (suit == 4) {return -1;}
    }

    // Return the integer value of the card
    return suit * 13 + rank;
}
int addCard (int cards[52], int card) {
//if the card is already in the deck, return 0, indicating a duplicate
    if (cards[card] == 1) {
        return 0;
    } else {
        cards[card] = 1;
        return 1;
    }
}
Card* loadDeck(const char *filename, SDL_Renderer *renderer) {
    FILE *file = fopen(filename, "r");
    char *message;
    if (file == NULL) {
       return NULL;
    }

    char buffer[2];
    Card *head = NULL, *tail = NULL;
    int cards[52] = {0};
    int card = -1;
    int i = 0;
    while (fscanf(file, "%2s", buffer) == 1) {
        card = card_to_int(buffer);
        if (card == -1) {return NULL;}
        //Add the card to its index in the cards array
        else if (addCard(cards, card) == 0) {return NULL;}
        Card *newCard = createCard(buffer[0], buffer[1]);
        newCard -> isFaceUp = 1;
        applyCardTexture(renderer, newCard);
        if (head == NULL) {
            head = newCard;
            tail = newCard;
        } else {
            tail->next = newCard;
            tail = newCard;
            tail -> next = NULL;
        }
        i++;
        if (i == 53) {return NULL;}
    }
    fclose(file);
    //return head;
    if (i != 52) {return NULL;}
    return head;
}

#include "LD.h"
