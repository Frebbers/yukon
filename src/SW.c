//
// Created by khaik on 07-04-2024.
//

#include "carddeck.h"
#include "stdlib.h"
#include "string.h"


char* displayDynamicInterface(Card* head) {
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char *foundations[] = {"F1", "F2", "F3", "F4"};
    char *message="Error: No deck loaded.";
    Card* current = head;
    int cardsPrinted=0;
    int rowCounter = 0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 7; col++) {
            if (current != NULL) {
                printf("\t%c%c", current->value, current->suit);
                current = current->next;
                cardsPrinted++;
                message = "OK";

            } else {

                printf("\t");
            }
        }
        if ((row)%2==0){
            printf("\t[]\t%s", foundations[rowCounter]);
            rowCounter++;
        }
        printf("\n");
    }
    printf("\n");
    return message;
}