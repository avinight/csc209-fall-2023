#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    // Read the first 2 command-line arguments into rodata_offset & rodata_size

    int rodata_offset = 0x2000;  // replace
    int rodata_size = 17;  // replace

   // Open the file named in the third argument




    // Allocate space for the .rodata section
    char *strings = malloc(sizeof(char) * rodata_size);
    if (strings == NULL) {
        perror("malloc");
        exit(1);
    }

    // Read the .rodata section


    // Format it for printing



    // Add a null terminating character to the end of the output so it is
    // safe to pass to printf
    strings[rodata_size - 1] = '\0';

    printf("%s\n", strings);
    free(strings);

    // close the file

    return 0;
}
