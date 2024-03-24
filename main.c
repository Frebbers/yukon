#include <stdio.h>
typedef struct {
    int* suit;
    int* value;
    struct Card* nextCard;
    

} Card;

int main() {

    int n = 4;
    int *lars = &n;

    //"*var =" kaldes referencing; fortæller C at var er en pointer
    //" = *var" kaldes dereferencing; hvilken værdi peger var på?
    //&var addressen af en variable
    int t = *lars






    printf("n = %d, lars = %d", n, *lars);

    return 0;


}
