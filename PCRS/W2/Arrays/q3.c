// Write a code fragment to loop over an array ages of count integers and print 
// the age of the second oldest. You may assume that count is at least 2.

#include <stdio.h>
int main() {
    // Variables count and ages are declared and initialized in hidden code.
// Submitted code below

    int oldest = ages[1];
    int second_oldest = ages[0];
    int i;
    for (i = 0; i < count; i++) {
        if (ages[i] > oldest) {
            oldest = ages[i];
        }
    }
    for (i = 0; i < count; i++) {
        if (ages[i] > second_oldest && ages[i] < oldest){
            second_oldest = ages[i];
        }
    }
    printf("%d", second_oldest);
// Submitted code above
    return 0;
}
// Submitted code below