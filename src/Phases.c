//
// Created by Magnus on 17/04/2024.
//
#include <string.h>
#include "phases.h"
#include "stdlib.h"
#include "carddeck.h"
#include "SW.h"
#include "board.h"


void startupPhase(){

}


void playPhase(Card **head) {
    int inPlayPhase = 1;
    char command[50] = "";
    char *message = "Enter a command during play phase";

    while (inPlayPhase) {
        printf("%s\n", message);
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;
        board();

        if (strcmp(command, "Q") == 0) {
            printf("Ending play phase.\n");
            inPlayPhase = 0;
        } else if (strcmp(command, "QQ") == 0 || strcmp(command, "SW") == 0 || strcmp(command, "SR") == 0
        || strcmp(command, "SI") == 0 || strcmp(command, "LD") == 0 || strcmp(command, "P") == 0)  {
            printf("Command not available during play phase.\n");
        } else{
            printf("Unknown command.\n");
        }
    }
}