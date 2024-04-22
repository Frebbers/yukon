
#include "carddeck.h"
#include "stdlib.h"
#include "string.h"

Column* createColumn(Card* card) {
    Column* newColumn = (Column*)malloc(sizeof(Column));
    if (newColumn == NULL) {
        printf("Error: Unable to allocate memory for new column.\n");
        return NULL;
    }
    newColumn->card = card;
    return newColumn;
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

void dealCards(Card *head) {
    // Constants for the game setup.
    const int totalCardsInColumns[7] = {1, 6, 7, 8, 9, 10, 11};
    const int faceUpStartIndex[7] = {0, 1, 2, 3, 4, 5, 6};

    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char *foundations[] = {"F1", "F2", "F3", "F4"};

    int counter = 0;

    int maxRows = 0;
    for (int i = 0; i < 7; i++) {
        if (totalCardsInColumns[i] > maxRows) {
            maxRows = totalCardsInColumns[i];
        }
    }

    // Create an array to hold the columns
    Column* columns[7] = {NULL};

    //Prints the cards in the columns
    Card *card = head;
    for (int row = 0; row < maxRows; row++) {
            printf("\t");

        for (int col = 0; col < 7; col++) {

            if ( row < totalCardsInColumns[col]) { // If the current row should have a card for this column.

                // Create a new column with the current card
                columns[col] = createColumn(card);

                if (card != NULL && row < faceUpStartIndex[col]) {
                     // Check if the card is face down.
                     printf("[  ]\t"); // Face down card representation.
                } else {
                    printf("[%c%c]\t", columns[col]->card->value, columns[col]->card->suit); // Face up card representation.
                        }

                card= card->next; // Move to the next card.

            } else {
                printf("\t"); // Empty space if there is no card in this column.
            }

        }

        //Prints the foundations
        if((row)%2 == 0 && row < 7){
            if(row == 0){
                    printf("\t[]\t%s\n",foundations[counter]);
                    counter++;
            }else if(row == 2){
                    printf("\t[]\t%s\n",foundations[counter]);
                    counter++;
            }else if(row == 4){
                    printf("\t[]\t%s\n",foundations[counter]);
                    counter++;
            }else if(row == 6){
                    printf("\t[]\t%s\n",foundations[counter]);
                    counter++;
            }
        }else{
            printf("\n");
        }

    }
}



