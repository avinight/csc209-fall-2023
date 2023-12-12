#include <stdio.h>

// Function prototype:
double my_fmax(double x, double y);

int main() {
    double larger_num = my_fmax(2, 3);
    printf("Of 2 and 3, the larger number is: %f \n", larger_num);

    return 0;
}

/* Returns the larger of two given values, x or y. */
double my_fmax(double x, double y) {
    if (x > y) {
        return x;
    }
    
    return y;
}
