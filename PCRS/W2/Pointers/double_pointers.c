#include <stdio.h>

/* set *largest_pt to the largest element pointed to by the array */
void find_largest(int **A, int A_size, int *largest_pt) {
    *largest_pt = **A;
    for (int i = 1; i < A_size; i++) {
        if (*A[i] > *largest_pt) {
            *largest_pt = *A[i];
        }
    }
}

int main() {

    int i = 81;
    int j = -4;
    // now A holds 2 pointers
    int *A[2] = {&j, &i};

    int largest;

    find_largest(A, 2, &largest);
    printf("largest is %d\n", largest);

    return 0;
}
