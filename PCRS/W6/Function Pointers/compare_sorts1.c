#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// compile this code with gcc -Wall compare_sorts.c sorts.c

// 3 sorts that we might like to try
void bubble_sort(int *, int);
void selection_sort(int *, int);
void insertion_sort(int *, int);

// confirm taht our sort works correctly
void check_sort(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i - 1] > arr[i]) {
            printf("Mis-sorted at index %d\n", i);
            return;
        }
    }
}


// fill arr with random values
void random_init(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}


/* Time a particular sort on an array of size integers */
double time_sort(int size) {
    int arr[size];
    random_init(arr, size);

    clock_t begin = clock();
    // To change the sort, we have to hardcode the new name and recompile
    //insertion_sort(arr, size);
    bubble_sort(arr, size);
    clock_t end = clock();

    check_sort(arr, size);

    return (double)(end - begin) / CLOCKS_PER_SEC;
}


int main() {
    srand(time(NULL));

    for (int size = 1; size <= 4096; size *= 2) {
        double time_spent = time_sort(size);
        printf("%d: %f\n", size, time_spent);
    }

    return 0;
}
