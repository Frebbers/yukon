#include <stdio.h>
#include <malloc.h>
#include "columns.h"
#include "carddeck.h"



/*char convertSuit(char suit) {
    if (suit == 'H' || suit == 'D') {
        return 'R';
    } else if (suit == 'S' || suit == 'C') {
        return 'B';
    }
    return '\0';

}*/

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

Column** columnFront(Card* card){
    Column** columns = malloc(11 * sizeof(Column*));
    for (int i = 0; i < 11; i++) {
        columns[i] = NULL;
    }

    createColumn(&columns[0], *card);
    card = card->next;
    for (int i = 1; i < 7; i++) {
        int count=1;

        while (count < i+6) {
            createColumn(&columns[i], *card);
            card = card->next;
            count++;
        }

        // Set the next field of the current column to point to the next column
        if (i < 6) { // Ensure we don't go out of bounds
            columns[i]->next = columns[i+1];
        }
    }

    // The last column's next should be NULL
    columns[6]->next = NULL;

    return columns;
}

Column** dealColumnsFront(Card* card){
    // Constants for the game setup.
    const int totalCardsInColumns[7] = {1, 6, 7, 8, 9, 10, 11};

    // Create an array to hold the columns and foundations
    Column** columns = malloc(11 * sizeof(Column*));
    // Initialize the columns and maxRows
    int maxRows = 20;
    for (int i = 0; i < 11; i++) {
        columns[i] = NULL;
    }


    //Creates and prints the cards in the columns
    for (int row = 0; row < maxRows; row++) {
        for (int col = 0; col < 7; col++) {
            if ( row < totalCardsInColumns[col]) { // If the current row should have a card for this column.
                createColumn(&columns[col], *card);
                card= card->next; // Move to the next card.
            }
        }

    }
    return columns;
}


Column** dealCards(Card* card){
    // Constants for the game setup.
    const int totalCardsInColumns[7] = {1, 6, 7, 8, 9, 10, 11};
    const int faceUpStartIndex[7] = {0, 1, 2, 3, 4, 5, 6};

    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char *foundations[] = {"F1", "F2", "F3", "F4"};


    // Create an array to hold the columns and foundations
    Column** columns = malloc(11 * sizeof(Column*));
    // Initialize the columns and maxRows
    int maxRows = 20;
    for (int i = 0; i < 11; i++) {
        columns[i] = NULL;
    }

    int counter = 0;
    //Creates and prints the cards in the columns
    for (int row = 0; row < maxRows; row++) {
        printf("\t");

        for (int col = 0; col < 7; col++) {

            if ( row < totalCardsInColumns[col]) { // If the current row should have a card for this column.

                if (card != NULL && row < faceUpStartIndex[col]) { // Check if the card is face down.
                    //set current card to face down
                    card->isFaceUp=0;
                    printf("[ ]\t"); // Face down card representation.

                } else {
                    printf("%c%c\t", card->value, card->suit); // Face up card representation.
                }
                // Create a new column with the current card
                createColumn(&columns[col], *card);
                card= card->next; // Move to the next card.

            } else {
                printf("\t"); // Empty space if there is no card in this column.
            }
        }

        //Prints the foundations
        if((row)%2 == 0 && row < 7){
            if(row == 0){
                printf("\t[]\t%s\n", foundations[counter]);
                counter++;
            }else if(row == 2){
                printf("\t[]\t%s\n", foundations[counter]);
                counter++;
            }else if(row == 4){
                printf("\t[]\t%s\n", foundations[counter]);
                counter++;
            }else if(row == 6){
                printf("\t[]\t%s\n", foundations[counter]);
                counter++;
            }
        }else{
            printf("\n");
        }

    }
    return columns;
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

//this function was used for testing purposes
void printColumns(Column** columns) {
    for (int i = 0; i < 11; i++) {
        printf("Column %d:\n", i + 1);
        Column* current = columns[i];
        while (current != NULL) {
            printf("Card Value: %c, Card Suit: %c, Face:%d\n", current->card->value, current->card->suit, current->card->isFaceUp);
            current = current->next;
        }
        printf("\n");
    }
}


Column** dealColumns(Column** columns){
    const int faceUpStartIndex[7] = {0, 1, 2, 3, 4, 5, 6};

    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char *foundations[] = {"F1", "F2", "F3", "F4"};

    int counter = 0;
    Column* firstCardInColumns[11];


    //Print the columns
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

                if (columns[col]->next != NULL && columns[col]->card->isFaceUp == 0) {
                    printf("[]\t"); // Face down card representation.
                } else {
                    columns[col]->card->isFaceUp=1;
                    printf("%c%c\t", columns[col]->card->value, columns[col]->card->suit); // Face up card representation.
                }

            } else {
                printf("\t"); // Empty space if there is no card in this column.
            }
        }
        //Prints the foundations

        if((row)%2 == 0 && row < 7){
            if(row == 0){
                if(columns[7]==NULL){
                    printf("\t[  ]\t%s\n",foundations[counter]);
                    counter++;
                } else {
                    Column *temp = columns[7];
                    Column *last = columns[7];
                    //print last card in the foundation column
                    while (temp != NULL) {
                        if (temp->next == NULL) {
                            last = temp;
                            break;
                        }
                        temp = temp->next;
                    }
                    printf("\t[%c%c]\t%s\n", last->card->value, last->card->suit, foundations[counter]);
                    counter++;
                }
            }else if(row == 2){
                if(columns[8]==NULL){
                    printf("\t[  ]\t%s\n",foundations[counter]);//print the foundation column if it's empty
                    counter++;
                } else {
                    Column *temp = columns[8];
                    Column *last = columns[8];

                    //print last card in the foundation column
                    while (temp != NULL) {
                        if (temp->next == NULL) {
                            last = temp;
                            break;
                        }
                        temp = temp->next;
                    }
                    printf("\t[%c%c]\t%s\n", last->card->value, last->card->suit, foundations[counter]);
                    counter++;
                }
            }else if(row == 4){
                if(columns[9]==NULL){
                    printf("\t[  ]\t%s\n",foundations[counter]);
                    counter++;
                } else {

                    Column *temp = columns[9];
                    Column *last = columns[9];

                    //print last card in the foundation column
                    while (temp != NULL) {
                        if (temp->next == NULL) {
                            last = temp;
                            break;
                        }
                        temp = temp->next;
                    }
                    printf("\t[%c%c]\t%s\n", last->card->value, last->card->suit, foundations[counter]);
                    counter++;
                }
            }else if(row == 6){
                if(columns[10]==NULL){
                    printf("\t[  ]\t%s\n",foundations[counter]);
                    counter++;
                } else {
                    Column *temp = columns[10];
                    Column *last = columns[10];

                    //print last card in the foundation column
                    while (temp != NULL) {
                        if (temp->next == NULL) {
                            last = temp;
                            break;
                        }
                        temp = temp->next;
                    }
                    printf("\t[%c%c]\t%s\n", last->card->value, last->card->suit, foundations[counter]);
                    counter++;
                }
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

char* moveCard(Column** sourceColumn, Column** destColumn, char value, char suit) {
    Column* current = *sourceColumn;
    Column* tempDest = *destColumn;
    Column* destCard = *destColumn;
    Column* prev = NULL;
    char *message = "";

    if(sourceColumn==destColumn){
        //printf("Source and destination columns are the same.\n");
         message="Error!_Source and destination columns are the same.\n";
        return message;
    }

    // Find the card the source column
    while (current != NULL) {
        if (current->card->value == value && current->card->suit == suit) {
            break;
        }
        prev = current;
        current = current->next;
    }


    // If the card is not found or is face down
    if (current == NULL || current->card->isFaceUp==0) {
        //printf("Card not found in source column.\n");
        message="Error!_Card not found in source column.\n";
        return message;
    }

    //Move if the destination column is empty
    if (tempDest ==NULL && current->card->value == 'K') {
        *destColumn = &(*current);

        //remove the card from the source column
        if (prev == NULL) {
            *sourceColumn = current->next;
        } else {
            prev->next = current;
            prev->next = NULL;
        }
        message="OK";
        return message;
    } else if (tempDest ==NULL && current->card->value != 'K') {
        //printf("Card %c%c is not King\n", current->card->value, current->card->suit);
         message="Error!_Card is not King\n";
        return message;
    }

    //Move if the destination column is not empty
    // get the last card from the destination column
    if (tempDest != NULL) {
        while (tempDest != NULL) {
            if (tempDest->next == NULL) {
                destCard = tempDest;

                // Check if the card can be moved to the destination column
                int destValue = convertValue(destCard->card->value);
                int currentValue = convertValue(current->card->value);
                if (destValue - 1 != currentValue || suit == destCard->card->suit || current->card->isFaceUp==0) {
                    /*printf("Invalid move: Card cannot be moved to destination column.\n");
                    printf("Current Value: %d, Destination Value: %d\n", currentValue, destValue);
                    printf("Current Suit: %c, Destination Suit: %c\n", current->card->suit, destCard->card->suit);*/
                    message="Error!_Invalid move: Card cannot be moved to destination column.\n";
                    return message;
                }

                // Add the card and all cards below to the destination column
                destCard->next = current;

                //remove the card from the source column
                if (prev == NULL) {
                    *sourceColumn = current->next;
                } else {
                    prev->next = current;
                    prev->next = NULL;
                    message="OK";
                    return message;
                }
                break;
            }
            tempDest = tempDest->next;
        }
    }
    return message;
}

char* moveCardToFoundation(Column** sourceColumn, Column** foundation, char value, char suit) {

    Column *current = *sourceColumn;
    Column *tempDest = *foundation;
    Column *destFound = *foundation;
    Column *prev = NULL;
    char *message = "";

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
        //printf("Card not found in source column.\n");
        message="Error!_Card not found in source column.\n";
        return message;
    }

    // If the destination column is empty
    if (tempDest == NULL && current->card->value == 'A') {
        if (current->next == NULL){
            createColumn(&(*foundation), *current->card);
        *foundation = &(*current);
        //remove the card from the source column
        if (prev == NULL) {
            *sourceColumn = current->next;
        } else {
            prev->next = current;
            prev->next = NULL;
        }
        message="OK";
        return message;
    } else if (current->next != NULL) {
        //printf("Card %c%c is not last in a column\n", current->card->value, current->card->suit);
        message="Error!_Card is not last in a column\n";
        return message;
    }

    } else if (tempDest == NULL && current->card->value != 'A') {
        if(current->next==NULL) {
            //printf("Card %c%c is not Ace\n", current->card->value, current->card->suit);
            message="Error!_Card is not Ace\n";
            return message;
        } else if (current->next != NULL) {
            //printf("Card %c%c is not last in a column\n", current->card->value, current->card->suit);
            message="Error!_Card is not last in a column\n";
            return message;
        }

    }

    //get the last card from the destination column
    if (tempDest != NULL) {
        while (tempDest != NULL) {
            if (tempDest->next == NULL) {
                destFound = tempDest;

                // Check if the card can be moved to the destination column
                int destValue = convertValue(destFound->card->value);
                int currentValue = convertValue(current->card->value);
                //char destSuit = convertSuit(destFound->card->suit);
                if ((destValue + 1) != currentValue || suit != destFound->card->suit || current->next != NULL || current->card->isFaceUp==0) {
                    //printf("Invalid move: Card cannot be moved to destination column.\n");
                    //printf("Current Value: %d, Destination Value: %d\n", currentValue, destValue);
                    //printf("Current Suit: %c, Destination Suit: %c\n", current->card->suit, destFound->card->suit);
                    //printf("Current Face: %d\n", current->card->isFaceUp);
                    message="Error!_Invalid move: Card cannot be moved to destination column.\n";
                    return message;
                }

                // Add the card to the destination column
                if ((destValue + 1) == currentValue && suit == destFound->card->suit && current->next == NULL) {
                    destFound->next = current;
                    //remove the card from the source column
                    if (prev == NULL) {
                        *sourceColumn = current->next;
                    } else {
                        prev->next = current;
                        prev->next = NULL;
                        message="OK";
                        return message;
                    }
                }
                break;
            }
            tempDest = tempDest->next;
        }
    }
    return message;
}

char* moveCardFromFoundation(Column** foundation, Column** destColumn, char value, char suit) {
    Column *current = *foundation;
    Column *tempDest = *destColumn;
    Column *destCard = *destColumn;
    Column *prev = NULL;
    char *message = "";

    // Find the card in the source foundation
    while (current != NULL) {
        if (current->card->value == value && current->card->suit == suit) {
            break;
        }
        prev = current;
        current = current->next;
    }
    // If the card is not found, return
    if (current == NULL) {
        //printf("Card not found in source foundation.\n");
        message="Error!_Card not found in source foundation.\n";
        return message;
    }

    // If the destination column is empty
    if (tempDest == NULL && current->card->value != 'A') {
        if (current->next == NULL){
            *destColumn = &(*current);

            //remove the card from the source column
            if (prev == NULL) {
                *foundation = current->next;
            } else {
                prev->next = current;
                prev->next = NULL;
            }
            message="OK";
            return message;
        } else if (current->next != NULL) {
            //printf("Card %c%c is not last in a column\n", current->card->value, current->card->suit);
            message="Error!_Card is not last in a column\n";
            return message;
        }

    } else if (tempDest == NULL && current->card->value == 'A') {
        if(current->next==NULL) {
            //printf("Ace can't be moved back in columns\n", current->card->value, current->card->suit);
            message="Error!_Ace can't be moved back in columns\n";
            return message;
        } else if (current->next != NULL) {
            //printf("Card %c%c is not last in a column\n", current->card->value, current->card->suit);
            message="Error!_Card is not last in a column\n";
            return message;
        }

    }

    //Move if the destination column is not empty
    // get the last card from the destination column
    if (tempDest != NULL) {
        while (tempDest != NULL) {
            if (tempDest->next == NULL) {
                destCard = tempDest;

                // Check if the card can be moved to the destination column
                int destValue = convertValue(destCard->card->value);
                int currentValue = convertValue(current->card->value);
                if (destValue - 1 != currentValue || suit == destCard->card->suit || current->next != NULL || current->card->isFaceUp==0) {
                    //printf("Invalid move: Card cannot be moved to destination column.\n");
                    //printf("Current Value: %d, Destination Value: %d\n", currentValue, destValue);
                    //printf("Current Suit: %c, Destination Suit: %c\n", current->card->suit, destCard->card->suit);
                    message="Error!_Invalid move: Card cannot be moved to destination column.\n";
                    return message;
                }

                // Add the card and all cards below to the destination column
                destCard->next = current;

                //remove the card from the source column
                if (prev == NULL) {
                    *foundation = current->next;
                } else {
                    prev->next = current;
                    prev->next = NULL;
                    message="OK";
                    return message;
                }
                break;
            }
            tempDest = tempDest->next;
        }
    }
    return message;
}