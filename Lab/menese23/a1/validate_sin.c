#include <stdio.h>
#include <stdlib.h>

int populate_array(int, int *);
int check_sin(int *);


int main(int argc, char **argv) {
    // TODO: Verify that command line arguments are valid.
    if (!(argc == 2)){
        return 2;
    }
    // TODO: Parse arguments and then call the two helpers in sin_helpers.c
    // to verify the SIN given as a command line argument.
    int sin = strtol(argv[1], NULL, 10);
    char *zero = "0";
    int array[9];

    populate_array(sin, array);
    if (check_sin(array) == 0 && argv[1][0] != *zero) {
        printf("%s", "Valid SIN\n");
        return 0;
    } 
    else {
        printf("%s", "Invalid SIN\n");
        return 1;
    }
}
