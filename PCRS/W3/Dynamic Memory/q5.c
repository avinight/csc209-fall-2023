#include <stdlib.h>
#include <stdio.h>
int main() {
    char **last_names;
    // Assign a dynamically allocated char * array of length 4 to last_names. 
    // Then, allocate a character array of length 20 for each element of the array 
    // pointed to by last_names.
	last_names = malloc(sizeof(char*) * 4);
    int i;
    for (i = 0; i < 4; i++) {
        last_names[i] = malloc(sizeof(char) * 20);
    }
    return 0;
}