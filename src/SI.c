//
// Created by frede on 17-04-2024.
//
#include "carddeck.h"
#include "SI.h"
#include <stdlib.h>
#include <time.h>

Card* splitShuffle(Card* oldDeck, int splitIndex) {
    // Initialize random number generator
    srand(time(NULL));

    //The shuffled deck to be returned
    Card* newDeck;
    //The first part of the deck. Length is equal to splitIndex
    Card *deck1;
    //The second part of the deck equal to 52-splitIndex
    Card *deck2;
    if (splitIndex < 1 || splitIndex > 52) {return oldDeck;}


    // Split the deck into two decks
    // Find the "splitIndex" card set its "next" pointer to NULL. Set Deck2 to point to that card.
    for (int i = 0; i < splitIndex; i++) {oldDeck = oldDeck->next;}
    Card *temp = oldDeck->next;
    oldDeck->next = NULL;
    deck2 = temp;
    deck1 = oldDeck;

    // Shuffle the cards
    //newDeck = *deck1;
    int i = 0;
    while (deck1 != NULL && deck2 != NULL) {
        if (i==0) {newDeck = deck1;}
        else {newDeck->next = deck1;}

                deck1 = deck1->next;
                newDeck->next = deck2;
                deck2 = deck2->next;
                i++;
    }
    if (deck1 != NULL) {newDeck->next = deck1;}
    if (deck2 != NULL) {newDeck->next = deck2;}


    return newDeck;
}


