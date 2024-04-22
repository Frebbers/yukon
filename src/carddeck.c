
#include "carddeck.h"
#include "stdlib.h"
#include "string.h"



void createColumn(Column** headColumn, Card card) {
    Column* newColumn = (Column*)malloc(sizeof(Column));
    newColumn->card = (Card*)malloc(sizeof(Card));

    *(newColumn->card) = card; // Copy the contents of card
    newColumn->next = *headColumn;
    *headColumn = newColumn;

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

    if(value == 'A'){
        return 1;
    } else if(value == '2'){
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

void freeColumns(Column** columns, int size) {
    for (int i = 0; i < size; i++) {
        Column* current = columns[i];
        while (current != NULL) {
            Column* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(columns);
}

/*Column** makeC(Card* card){
    // Create an array to hold the columns
    Column** columns = malloc(2 * sizeof(Column*));

// Initialize the columns
    for (int i = 0; i < 2; i++) {
        columns[i] = NULL;
    }

    for (int i = 0; card != NULL; i = (i + 1) % 2) {
        createColumn(&columns[i], *card);
        card = card->next;
    }

    return columns;
}*/

void printColumns(Column** columns) {
    for (int i = 0; i < 7; i++) {
        printf("Column %d:\n", i + 1);
        Column* current = columns[i];
        while (current != NULL) {
            printf("Card Value: %c, Card Suit: %c\n", current->card->value, current->card->suit);
            current = current->next;
        }
        printf("\n");
    }
}

void findAndPrintCardInColumn(Column* column, char value, char suit) {
    while (column != NULL) {
        if (column->card->value == value && column->card->suit == suit) {
            printf("Card found: Value: %c, Suit: %c\n", column->card->value, column->card->suit);
            return;
        }
        column = column->next;
    }
    printf("Card not found.\n");
}
void moveCard(Column** sourceColumn, Column** destColumn, char value, char suit) {
    Column* current = *sourceColumn;
    Column* tempDest = *destColumn;
    Column* destCard = *destColumn;
    Column* prev = NULL;

    // Find the card in the source column
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

    //get the last card from the destination column
    while (tempDest != NULL) {
        if (tempDest->next == NULL) {
            destCard = tempDest;
            break;
        }
        tempDest = tempDest->next;
    }
    // compare too char




    // Check if the card can be moved to the destination column
    int destValue = convertValue(destCard->card->value);
    int currentValue = convertValue(current->card->value);
    char sourceSuit = convertSuit(current->card->suit);
    char destSuit = convertSuit(destCard->card->suit);
    if (destValue - 1 != currentValue || sourceSuit == destSuit) {
        printf("Invalid move: Card cannot be moved to destination column.\n");
        printf("Current Value: %d, Destination Value: %d\n", currentValue, destValue);
        printf("Current Suit: %c, Destination Suit: %c\n", sourceSuit, destSuit);
        return;
    }

    // Remove the card from the source column
    if (prev == NULL) {
        *sourceColumn = current->next;
    } else {
        prev->next = current->next;
    }

        // Add the card to the destination column


    current->next = *destColumn;
    *destColumn = current;
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



/*void dealCards(Card *head) {
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
    Column* column[7] = {NULL};

    //Prints the cards in the columns
    Card *card = head;
    for (int row = 0; row < maxRows; row++) {
            printf("\t");

        for (int col = 0; col < 7; col++) {

            if ( row < totalCardsInColumns[col]) { // If the current row should have a card for this column.

                // Create a new column with the current card
                column[col] = createColumn(card);

                if (card != NULL && row < faceUpStartIndex[col]) {
                     // Check if the card is face down.
                     printf("[  ]\t"); // Face down card representation.
                } else {
                    printf("[%c%c]\t", column[col]->card->value, column[col]->card->suit); // Face up card representation.
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
}*/

Column** dealCards(Card* card){
    // Constants for the game setup.
    const int totalCardsInColumns[7] = {1, 6, 7, 8, 9, 10, 11};
    const int faceUpStartIndex[7] = {0, 1, 2, 3, 4, 5, 6};

    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char *foundations[] = {"F1", "F2", "F3", "F4"};

    // Create an array to hold the columns
    Column** columns = malloc(7 * sizeof(Column*));
    // Initialize the columns and maxRows
    int maxRows = 0;
    for (int i = 0; i < 7; i++) {
        columns[i] = NULL;
        if (totalCardsInColumns[i] > maxRows) {
            maxRows = totalCardsInColumns[i];
        }

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





    for (int i = 0; card != NULL; i = (i + 1) % 2) {
        createColumn(&columns[i], *card);
        card = card->next;
    }
  return columns;
}







