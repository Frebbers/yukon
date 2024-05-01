
#include "carddeck.h"
#include "stdlib.h"
#include "string.h"



Card* createCard(char value, char suit) {
    Card* newCard = (Card*)malloc(sizeof(Card));
    if (newCard == NULL) {
        printf("Error: Unable to allocate memory for new card.\n");
        return NULL;
    }
    newCard->suit = suit;
    newCard->value = value;
    newCard->isFaceUp = 0;

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

char convertSuit(char suit) {
    if (suit == 'H' || suit == 'D') {
        return 'R';
    } else if (suit == 'S' || suit == 'C') {
        return 'B';
    }
    return '\0';

}

int convertValue(char value) {

    if(value == 'A' || value == '1') {
        return 1;
    }else if(value == '2'){
        return 2;
    }else if(value == '3'){
        return 3;
    }else if(value == '4'){
        return 4;
    }else if(value == '5') {
        return 5;
    }else if(value == '6') {
        return 6;
    }else if(value == '7') {
        return 7;
    }else if(value == '8') {
        return 8;
    }else if(value == '9') {
        return 9;
    }else if(value == 'T'){
        return 10;
    }else if(value == 'J'){
        return 11;
    }else if(value == 'Q'){
        return 12;
    }else if(value == 'K'){
        return 13;
    }
    return 0;

}

void moveCard(Column** sourceColumn, Column** destColumn, char value, char suit) {
    Column* current = *sourceColumn;
    Column* tempDest = *destColumn;
    Column* destCard = *destColumn;
    Column* prev = NULL;


    char *message = "";


    // Find the card and end column

    while (current != NULL) {
        if (current->card->value == value && current->card->suit == suit) {
                 break;
        }
        prev = current;
        current = current->next;
    }


    // If the card is not found, return
    if (current == NULL) {
        printf("Card not found in source column.\n");
        return;
    }


    if (tempDest ==NULL && current->card->value == 'K') {
        *destColumn = &(*current);
        //remove the card from the source column
        if (prev == NULL) {
            *sourceColumn = current->next;
        } else {
            prev->next = current->next;
        }

        return;
    } else if (tempDest ==NULL && current->card->value != 'K') {
        printf("Card %c%c\n is not King", current->card->value, current->card->suit);
        return;
    }

    //get the last card from the destination column
    if (tempDest != NULL) {
        while (tempDest != NULL) {
            if (tempDest->next == NULL) {
                destCard = tempDest;

                // Check if the card can be moved to the destination column
                int destValue = convertValue(destCard->card->value);
                int currentValue = convertValue(current->card->value);
                char sourceSuit = convertSuit(current->card->suit);
                char destSuit = convertSuit(destCard->card->suit);
                if (destValue - 1 != currentValue || sourceSuit == destSuit) {
                    printf("Invalid move: Card cannot be moved to destination column.\n");
                    printf("Current Value: %d, Destination Value: %d\n", currentValue, destValue);
                    printf("Current Suit: %c, Destination Suit: %c\n", current->card->suit, destCard->card->suit);
                    return;
                }

                // Add the card and all cards below to the destination column
                destCard->next = current;

                break;
            }
            tempDest = tempDest->next;
            //remove the card from the source column
            if (prev == NULL) {
                *sourceColumn = current->next;
            } else {
                prev->next = current->next;
            }
        }
    }
}

void createColumn(Column** headColumn, Card card) {
    Column* newColumn = (Column*)malloc(sizeof(Column));
    newColumn->card = (Card*)malloc(sizeof(Card));

    *(newColumn->card) = card; // Copy the contents of card
    newColumn->next = NULL; // The new column is the last one, so its next is NULL

    if (*headColumn == NULL) {
        *headColumn = newColumn; // If the column is empty, the new column is the head
    } else {
        Column* lastColumn = *headColumn;
        while(lastColumn->next != NULL) {
            lastColumn = lastColumn->next; // Find the last column
        }
        lastColumn->next = newColumn; // The last column's next is the new column
    }
}


Column** dealCards(Card* card){
    // Constants for the game setup.
    const int totalCardsInColumns[7] = {1, 6, 7, 8, 9, 10, 11};
    const int faceUpStartIndex[7] = {0, 1, 2, 3, 4, 5, 6};

    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char *foundations[] = {"F1", "F2", "F3", "F4"};
    Card *fn = (Card*)malloc(sizeof(Card));

    // Create an array to hold the columns
    Column** columns = malloc(11 * sizeof(Column*));
    // Initialize the columns and maxRows
    int maxRows = 20;
    for (int i = 0; i < 11; i++) {
        columns[i] = NULL;
    }

   int counter = 0;
    //Prints the cards in the columns
   for (int row = 0; row < maxRows; row++) {
        printf("\t");

        for (int col = 0; col < 7; col++) {

            if ( row < totalCardsInColumns[col]) { // If the current row should have a card for this column.

                // Create a new column with the current card
                createColumn(&columns[col], *card);

                if (card != NULL && row < faceUpStartIndex[col]) {
                    // Check if the card is face down.
                    printf("[  ]\t"); // Face down card representation.

                } else {
                    printf("[%c%c]\t", card->value, card->suit); // Face up card representation.
                }
                card= card->next; // Move to the next card.

            } else {
                printf("\t"); // Empty space if there is no card in this column.
            }
        }

        //Prints the foundations
        if((row)%2 == 0 && row < 7){
            if(row == 0){

                createColumn(&columns[7], *fn);
                printf("\t[]\t%s\n",foundations[counter]);
                counter++;
            }else if(row == 2){
                createColumn(&columns[8], *fn);
                printf("\t[]\t%s\n",foundations[counter]);
                counter++;
            }else if(row == 4){
                createColumn(&columns[9], *fn);
                printf("\t[]\t%s\n",foundations[counter]);
                counter++;
            }else if(row == 6){
                createColumn(&columns[10], *fn);
                printf("\t[]\t%s\n",foundations[counter]);
                counter++;
            }
        }else{
            printf("\n");
        }

    }

  return columns;
}


void printColumns(Column** columns) {
    for (int i = 0; i < 11; i++) {
        printf("Column %d:\n", i + 1);
        Column* current = columns[i];
        while (current != NULL) {
            printf("Card Value: %c, Card Suit: %c\n", current->card->value, current->card->suit);
            current = current->next;
        }
        printf("\n");
    }
}


Card* reverseDealCards(Column** columns) {
    Card *newDeck = NULL;
    Card *head = NULL;

    int cards = 0;
    //copy the columns to a new deck
    while(cards<52) {

        for (int i = 0; i < 7; i++) {
            Column *current = columns[i];
            Column *temp = current;
            Card* copyCard = NULL;
            if (current != NULL) {
                //copy current card to copyCard
                appendCard(&copyCard, current->card->value, current->card->suit);
                //delete current card from this column
                current = current->next;
                columns[i] = current;
                free(temp);
                //put the copyCard to the new deck
                if (head == NULL) {
                    head = copyCard;
                    newDeck = head;
                } else {
                    newDeck->next = copyCard;
                    newDeck = newDeck->next;
                }
                cards++;
            }
        }

    }
    return head;
}
Column** dealColumns(Column** columns){

    const int faceUpStartIndex[7] = {0, 1, 2, 3, 4, 5, 6};

    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char *foundations[] = {"F1", "F2", "F3", "F4"};

    int counter = 0;
    //Prints the cards in the columns
    Column* firstCardInColumns[7];

    for (int row = 0; row < 20; row++) {
        printf("\t");

        for (int col = 0; col < 7; col++) {
            // Reset the pointer to the first card in the column for each new row
            if (row == 0) {
                firstCardInColumns[col] = columns[col];
            } else {
                columns[col] = firstCardInColumns[col];
            }

            // Move to the card in the current row
            int getRow = 0;
            while (getRow < row && columns[col] != NULL) {
                columns[col] = columns[col]->next;
                getRow++;
            }





            // Print the card
            if (columns[col] != NULL) {
                int count = 0;
                if (row < faceUpStartIndex[col] && columns[col]->next!=NULL) {
                    printf("[]\t"); // Face down card representation.
                } else {
                    printf("%c%c\t", columns[col]->card->value, columns[col]->card->suit); // Face up card representation.
                }
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
    //reset columns pointer to the first card in the columns
    for (int i = 0; i < 7; i++) {
        columns[i] = firstCardInColumns[i];
    }
    return columns;
}


void moveCardToFoundation(Column** sourceColumn, Column** foundation, char value, char suit) {

    Column* current = *sourceColumn;
    Column* tempDest = *foundation;
    Column* destFound = *foundation;
    Column* prev = NULL;
    char *message = "";

    // Find the card in the source column and remove it
    while (current != NULL) {
        if (current->card->value == value && current->card->suit == suit) {
            if (prev == NULL) {
                *sourceColumn = current->next;
            } else {
                prev->next = current->next;
            }
            current->next = NULL;
            break;
        }
        prev = current;
        current = current->next;
    }
    printf("Card %c%c\n", current->card->value, current->card->suit);

    // If the card is not found, return
    if (current == NULL) {
        printf("Card not found in source column.\n");
        return;
    }

        //get the last card from the destination column
        if (tempDest ==NULL){
            createColumn(&tempDest, *current->card);
        } else {
            while (tempDest != NULL) {
                if (tempDest->next == NULL) {
                    destFound = tempDest;
                    break;
                }
                tempDest = tempDest->next;
            }
        }

        destFound->next = current;
}

