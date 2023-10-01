#include <stdio.h>
#include <stdlib.h>

int play_with_memory() {
    int i;
    int *pt = malloc(sizeof(int));

    i = 15;
    *pt = 49;
    
    // What happens if you comment out this call to free?
    free(pt);

    // What happens if you uncomment these statements?
    // printf("%d\n", *pt);
    // *pt = 7;

    // printf("%d\n", *pt);

    return 0;
}

int main() {
    play_with_memory();
    play_with_memory();
    play_with_memory();
    return 0;
}
    
    
