#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a node in the linked list
typedef struct Card {
    char value[3];
    struct Card *next;
} Card;

// Function to create a new card node
Card* createCard(const char *value) {
    Card *newCard = (Card *)malloc(sizeof(Card));
    if (newCard) {
        strcpy(newCard->value, value);
        newCard->next = NULL;
    }
    return newCard;
}

// Function to load the deck from a file into a linked list
Card* loadDeck(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: No deck loaded.\n");
        return NULL;
    }

    char buffer[3];
    Card *head = NULL, *tail = NULL;

    while (fscanf(file, "%2s", buffer) == 1) {
        Card *newCard = createCard(buffer);
        if (head == NULL) {
            head = newCard;
            tail = newCard;
        } else {
            tail->next = newCard;
            tail = newCard;
        }
    }

    fclose(file);
    return head;
}

// Function to display the static parts of the interface
void displayStaticInterface() {
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");
   // printf("\t[]\t[]\t[]\t[]\t[]\t[]\t[]\n");
    printf("\t\t\t\t\t\t\t\t[] F1\n");
    printf("\t\t\t\t\t\t\t\t[] F2\n");
    printf("\t\t\t\t\t\t\t\t[] F3\n");
    printf("\t\t\t\t\t\t\t\t[] F4\n\n");
}

// Function to display the deck
// Function to display the deck
void displayDeck(Card *deck) {
    if (deck == NULL) {
        printf("Error: No deck loaded.\n");
        return;
    }

    // Print the column headers for C1 - C7
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n");

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


int main() {
    Card *deck = NULL;
    char lastCommand[50] = "";
    char message[100] = "";

    while (1) {
        // Clear the console (uncomment next line if you are on Windows or use `clear` for Unix-like systems)
        // system("cls"); // Windows
        // system("clear"); // Unix/Linux/Mac

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

        // If 'SW' command is entered
        if (strcmp(command, "SW") == 0) {
            strcpy(lastCommand, "SW");
            const char *filename = "rsc/cards.txt";
            deck = loadDeck(filename);
            if (deck != NULL) {
                strcpy(message, "OK");
            } else {
                strcpy(message, "Error: No deck loaded.");
            }
        } else {
            strcpy(lastCommand, command);
            strcpy(message, "Unknown command.");
        }
    }

    // Normally you would free the linked list memory here, but since this is a continuous loop,
    // it would only be reached when the program exits.
    // When implementing an 'exit' command or similar, make sure to free the memory and break the loop.

    return 0;
}
