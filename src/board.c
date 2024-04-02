#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "carddeck.h"

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
