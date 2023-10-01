#include <stdio.h>
#include <stdlib.h>

// TODO: Implement populate_array
/*
 * Convert a 9 digit int to a 9 element int array.
 */
int populate_array(int sin, int *sin_array) {
    for (int i = 8; i >= 0; i--){
        int digit = sin % 10;
        sin = sin / 10;
        sin_array[i] = digit;
    }
    return 0;
}

// TODO: Implement check_sin
/*
 * Return 0 if the given sin_array is a valid SIN, and 1 otherwise.
 */
int check_sin(int *sin_array) {
    int int_to_multiply[9] = {1, 2, 1, 2, 1, 2, 1, 2, 1};
    int digit;
    int sum;
    for (int i = 0; i < 9; i++){
        digit = sin_array[i] * int_to_multiply[i] % 10;
        digit += sin_array[i] * int_to_multiply[i] / 10; 
        sum += digit;
    }
    if (sum % 10 == 0){
        return 0;
    }
    return 1;
}
