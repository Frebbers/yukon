//
// Created by frede on 17-04-2024.
//
#include "carddeck.h"
#include "SI.h"
#include <stdlib.h>
#include <time.h>

Deck* splitShuffle(Deck* oldDeck) {
    // Initialize random number generator
    srand(time(NULL));

    // Reserve memory for the new deck and two 26-card decks
    Deck* newDeck = (Deck*)malloc(sizeof(Deck));
    Card* deck1[26];
    Card* deck2[26];

    // Distribute the first 26 cards into deck1 and the next 26 into deck2
    for (int i = 0; i < 26; i++) {
        deck1[i] = removeCard(oldDeck);
        deck2[i] = removeCard(oldDeck);
    }

    // Shuffle the cards
    int i = 0, j = 0;
    while (i < 26 && j < 26) {
        int randNum = rand() % 2;
        if (randNum == 0) {
            addCard(newDeck, deck1[i]);
            i++;
        } else {
            addCard(newDeck, deck2[j]);
            j++;
        }
    }

    // Add the remaining cards from the non-empty deck to the new deck
    while (i < 26) {
        addCard(newDeck, deck1[i]);
        i++;
    }
    while (j < 26) {
        addCard(newDeck, deck2[j]);
        j++;
    }

    // Free the memory allocated for deck1 and deck2
    for (i = 0; i < 26; i++) {
        free(deck1[i]);
        free(deck2[i]);
    }

    return newDeck;
}


