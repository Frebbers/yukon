//
// Created by Magnus on 17/04/2024.
//
#include <string.h>
#include "stdlib.h"
#include "carddeck.h"
#include "SW.h"
#include "board.h"


void startupPhase(){

}

 char* playPhase(char* function){
    int inPlayPhase = 1;
    char command[50] = "";
    char *message = " ";

    while (inPlayPhase) {
       if (strcmp(function, "Q") == 0) {
            message="Ending play phase.";
            inPlayPhase = 0;
        } else if (strcmp(function, "QQ") == 0 || strcmp(function, "SW") == 0 || strcmp(function, "SR") == 0
        || strcmp(function, "SI") == 0 || strcmp(function, "LD") == 0 || strcmp(function, "P") == 0)  {
            message="Command not available during play phase.";
            return message;
        } else{
            message= "Unknown command.";
            return message;
        }
    }
    return message;
}