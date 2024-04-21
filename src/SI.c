//
// Created by frede on 17-04-2024.
//
#include "carddeck.h"
#include "SI.h"
#include <stdlib.h>
#include <time.h>

Card* splitShuffle(Card* oldDeck) {
    // Initialize random number generator
    srand(time(NULL));

    // Reserve memory for the new deck and two 26-card decks
    Card* newDeck = NULL;
    Card* deck1[26];
    Card* deck2[26];

    // Distribute the first 26 cards into deck1 and the next 26 into deck2
    for (int i = 0; i < 26; i++) {
        deck1[i] = oldDeck;
        oldDeck = oldDeck->next;
        deck2[i] = oldDeck;
        oldDeck = oldDeck->next;
    }

    // Shuffle the cards
    newDeck = deck1[0];
    int i = 1, j = 0;
    while (i < 26 && j < 26) {
        int randNum = rand() % 2;
        if (randNum == 0) {
            appendCard(&newDeck, deck1[i]->value, deck1[i]->suit);
            if (newDeck->next != NULL) {
                newDeck = newDeck->next;
            }
            i++;
        } else {
            appendCard(&newDeck, deck2[j]->value, deck2[j]->suit);
            if (newDeck->next != NULL) {
                newDeck = newDeck->next;
            }
            j++;
        }
    }

    // Add the remaining cards from the non-empty deck to the new deck
    while (i < 26) {
        appendCard(&newDeck, deck1[i]->value, deck1[i]->suit);
        if (newDeck->next != NULL) {
            newDeck = newDeck->next;
        }
        i++;
    }
    while (j < 26) {
        appendCard(&newDeck, deck2[j]->value, deck2[j]->suit);
        if (newDeck->next != NULL) {
            newDeck = newDeck->next;
        }
        j++;
    }

    // Free the memory allocated for deck1 and deck2
   /* for (i = 0; i < 26; i++) {
        free(deck1[i]);
        free(deck2[i]);
    }
*/
    return newDeck;
}


