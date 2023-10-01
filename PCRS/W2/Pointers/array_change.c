#include <stdio.h>

int change(int *A) {
    // We explicitly change element 0 to 50 
    // in order to demonstrate that this change
    // lasts in the array that was passed to the function
    A[0] = 50;
}


int main() {

    int scores[4];
    // set the first element to 4
    scores[0] = 4;

    // call the function which is supposed to change it to 50
    change(scores);

    // What will be printed?
    // Will the function have changed the array scores or just a local
    // copy of that array?
    printf("First element in array has value %d\n", scores[0]);
    return 0;

    // When the function call takes place, the value passed to some_function is only the address of year. 
    // It is possible for some_function to change the values in year but not its address. 
    int year[5] = {1992, 2015, 1965, 1990, 1984};
    change(year);
    // MARKER
}
