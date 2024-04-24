//
// Created by frede on 17-04-2024.
//
#include "carddeck.h"
#include "SI.h"
#include <stdlib.h>
#include <time.h>

Card* splitShuffle(Card* oldDeck, int splitIndex) {
    //The shuffled deck to be returned
    Card* newDeck;
    //The first part of the deck. Length is equal to splitIndex
    Card *deck1 = oldDeck;
    //The second part of the deck equal to 52-splitIndex
    Card *deck2;
    if (splitIndex < 1 || splitIndex > 52) {return oldDeck;}
    // Split the deck into two decks
    // Find the "splitIndex" card set its "next" pointer to NULL. Set Deck2 to point to that card.
    for (int i = 0; i < splitIndex; i++) {oldDeck = oldDeck->next;}
    Card *temp = oldDeck->next;
    oldDeck->next = NULL;
    deck2 = temp;

    // Shuffle the cards
    //newDeck = *deck1;
    //TODO  add pointer to start of newdeck
   int i = 0;
    Card *newDeckTemp;
    while (deck1 != NULL && deck2 != NULL) {
        if (i==0) {
            newDeck = deck1;
            newDeckTemp = newDeck;
        }
        else {newDeck->next = deck1;
        newDeck = newDeck->next;}

                deck1 = deck1->next;
                newDeck->next = deck2;
                newDeck = newDeck->next;
                deck2 = deck2->next;
                i++;
    }
    if (deck1 != NULL) {newDeck->next = deck1;}
    if (deck2 != NULL) {newDeck->next = deck2;}
    //Point the head of the linked list to the start of the shuffled deck
    newDeck = newDeckTemp;
    return newDeck;
}


