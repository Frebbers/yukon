#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "carddeck.h"



void board();

char* handleInput(char* message, char command[50]) {
    char* input=malloc(sizeof(char) * 50); //dynamically allocate a specified amount of memory
    printf("LAST Command: %s\n", command);
    printf("Message: %s \n",message);
    printf("INPUT > ");
    fgets(input, 50, stdin);     // reads input from user
    return input;
}


