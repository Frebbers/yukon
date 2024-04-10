//
// Created by khaik on 07-04-2024.
//
#include <stdlib.h>
#include "carddeck.h"
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

Card * SR(Card *head) {
    //Initializing data
    char *message = "Error happened during the shuffling";
    Card *current=head;
    Card *newHead = NULL;
    Card *newTail = NULL;
    int size[52];
    int index = 0;
    char buffer[2];
    int counter = 0;
    int deckSize = 0;
    int random;

 /*   while(counter < 52){
        buffer[0] = head->value;
        buffer[1] = head->suit;
        createCard(buffer[0], buffer[1]);
        head = head -> next;
        counter++;
    }*/




    //get 52 random numbers
    srand(time(NULL));
    for (index = 0; index < 52; index++) {
        size[index] = index;
    }
    for (index = 51; index > 0; index--) {
        int j = rand() % (index + 1);
        swap(&size[index], &size[j]);
    }


//shuffling the deck
   for (index = 0; index < 52; index++) {
       random = size[index];
       while (counter < random) {
           head = head->next;
           counter++;
       }
       current = head;
       buffer[0] = current->value;
       buffer[1] = current->suit;


       Card *newCard = createCard(buffer[0], buffer[1]);
       if (newHead == NULL) {
           newHead = newCard;
           newTail = newCard;
       } else {
           newTail->next = newCard;
           newTail = newCard;
       }
   }
    saveDeck(newHead);
       return newHead;

}

#include "SR.h"
