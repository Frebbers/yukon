#include <stdio.h>
#include <malloc.h>


void board() {
    char *foundations[] = {"F1", "F2", "F3", "F4\n"};
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    int index = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            printf("\t");
        }
        if((i)%2 == 0){
            printf("\t[] %s",foundations[index]);
            if(i != 6){
                printf("\n");
            }
            index++;
        }else{
            printf("\n");
        }
    }
}

void loadedDeck() {
    printf("\tC1\tC2\tC3\tC4\tC5\tC6\tC7\n\n");
    char *foundations[] = {"F1", "F2", "F3", "F4"};
    int index = 0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 7; col++) {
            printf("\t[]");

        }
        if ((row)%2==0){
            printf("\t[]\t%s", foundations[index]);
            index++;
        }
        printf("\n");
    }
    printf("\n");
}

char* handleInput(char* message, char command[50]) {
    char* input=malloc(sizeof(char) * 50); //dynamically allocate a specified amount of memory
    printf("LAST Command: %s\n", command);
    printf("Message: %s \n",message);
    printf("INPUT > ");
    fgets(input, 50, stdin);     // reads input from user
    return input;
}


