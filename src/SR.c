//
// Created by khaik on 07-04-2024.
//
#include <stdlib.h>
#include "carddeck.h"
#include <stdlib.h>
#include <time.h>



Card * SR(Card *head) {

    Card *copyCard =NULL;
    Card *temp = head;
    Card *shuffledPile = NULL; // The shuffled pile starts out empty
    int counter = 0;

    // Copy the unshuffled pile to a new pile
    while(temp != NULL) {
        appendCard(&copyCard, temp->value, temp->suit);
        temp = temp->next;
    }

    temp = copyCard;
    while (temp != NULL) {
        // Remove the top card from the unshuffled pile
        Card *currentCard = temp;
        Card *nextTemp = temp->next;
        temp->next = NULL;
        temp = nextTemp;

        srand(time(NULL)); // Seed the random number generator
        // Generate a random position to insert the card in the shuffled pile
        int position = rand() % (counter + 1);

        // Insert the card at the random position
        if (position == 0) {
            // Insert at the head of the shuffled pile
            currentCard->next = shuffledPile;
            shuffledPile = currentCard;
        } else {
            // Insert at the given position
            Card *current = shuffledPile;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }
            currentCard->next = current->next;
            current->next = currentCard;
        }

        counter++; // Increase the size of the shuffled pile
    }

    return shuffledPile; // Return the shuffled pile as the new deck
}


#include "SR.h"
