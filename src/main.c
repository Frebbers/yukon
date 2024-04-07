#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carddeck.h"
#include "carddeck.c"


// Function to display the static parts of the interface
void displayStaticInterface() {
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");
   // printf("\t[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
    printf("\t\t\t\t\t\t\t\t[] F1\n");
    printf("\t\t\t\t\t\t\t\t[] F2\n");
    printf("\t\t\t\t\t\t\t\t[] F3\n");
    printf("\t\t\t\t\t\t\t\t[] F4\n\n");
}


void displayDeck(Card *deck) {
    if (deck == NULL) {
        printf("Error: No deck loaded.\n");
        return;
    }


    Card *current = deck;
    int cardsInColumn = 0;

    // Since we want to display the cards in a grid-like structure,
    // determine how many cards go into each column
    while (current != NULL) {
        printf("\t%s", current->value);
        current = current->next;
        cardsInColumn++;

        if (cardsInColumn == 7) { // After printing 7 cards, move to the next line
            printf("\n");
            cardsInColumn = 0; // Reset the count for the new line
        }
    }

    // If the number of cards is not a multiple of 7, we need to
    // end the current line after printing the last card
    printf("\n");

}

#include "board.h"

int main() {
    Card *deck = NULL;
    char lastCommand[50] = "";
    char message[100] = "";

    while (1) {

        displayStaticInterface();

        // If deck is loaded, display it
        if (deck != NULL) {
            displayDeck(deck);
        }

        printf("LAST Command: %s\n", lastCommand);
        printf("Message: %s\n", message);
        printf("INPUT > ");
        char command[3];
        scanf("%2s", command);

        if (strcmp(command, "SW") == 0) {
            strcpy(lastCommand, "SW");
            const char *filename = "rsc/cards.txt";
            deck = loadDeck(filename);
            if (deck != NULL) {
                strcpy(message, "OK");
            } else {
                strcpy(message, "Error: No deck loaded.");
            }
        } else if (strcmp(command,"QQ") == 0){
            freeDeck(deck);
            printf("The program exits.");
            exit(0);
        } else {
            strcpy(lastCommand, command);
            strcpy(message, "Unknown command.");
        }
    }



    return 0;
}

