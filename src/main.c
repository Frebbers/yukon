#include <stdio.h>
#include "stdlib.h"
#include "carddeck.h"
#include "board.h"

void staticInterface(){
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    printf("\t\t\t\t\t\t\t\t[] F1\n\n");
    printf("\t\t\t\t\t\t\t\t[] F2\n\n");
    printf("\t\t\t\t\t\t\t\t[] F3\n\n");
    printf("\t\t\t\t\t\t\t\t[] F4\n\n");
}

void displayDynamicInterface(Card* head) {
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    Card* current = head;
    int cardsPrinted=0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 7; col++) {
            if (current != NULL) {
                printf("\t%s", current->value);
                current = current->next;
                cardsPrinted++;
            } else {
                printf("\t[]");
            }
        }
        // Virkelig grimt at se på her, men we ball - skal ændres fuldkommen senere
        if (row == 0) {
                printf("\t[] F1");
        }
        if (row == 2) {
            printf("\t[] F2");
        }
        if (row == 4) {
            printf("\t[] F3");
        }
        if (row == 6) {
            printf("\t[] F4");
        }
        printf("\n");
    }
    printf("\n");
}




int main() {
    Card *deck = NULL;
    Card *head = NULL;
    char lastCommand[50] = "";
    char message[100] = "";
    staticInterface();
    while (1) {

        printf("LAST Command: %s\n", lastCommand);
        printf("Message: %s\n", message);
        printf("INPUT > ");
        char command[3];
        scanf("%2s", command);

        if (strcmp(command, "SW") == 0) {
            strcpy(lastCommand, "SW");
            const char *filename = "rsc/cards.txt";
            Card* newDeck = loadDeck(filename);
            if (newDeck != NULL) {
                if (deck != NULL) {
                    freeDeck(deck);
                }
                deck = newDeck;
                head = deck;
                strcpy(message, "OK");
            } else {
                strcpy(message, "Error: No deck loaded.");
            }
        } else if (strcmp(command,"QQ") == 0){
            char full[_MAX_PATH];
            _fullpath(full,"rsc/savedcards.txt" , _MAX_PATH);
            saveDeck(head, full);

            freeDeck(deck);
            printf("The program exits.");
            exit(0);
        } else {
            strcpy(lastCommand, command);
            strcpy(message, "Unknown command.");
        }
        displayDynamicInterface(head);
    }

    return 0;
}

