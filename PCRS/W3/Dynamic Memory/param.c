#include <stdio.h>
#include <stdlib.h>

void helper(int **arr_matey) {
   // let's make an array of 3 integers on the heap
   *arr_matey = malloc(sizeof(int) * 3);

   int *arr = *arr_matey;
   arr[0] = 18;
   arr[1] = 21;
   arr[2] = 23;
}

int main() {
    int *data;
    helper(&data);

    // let's just access one of them for demonstration
    printf("the middle value: %d\n", data[1]);

    free(data);
    return 0;
}
