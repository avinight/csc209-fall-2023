#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_image(int num_rows, int num_cols, 
                int arr[num_rows][num_cols], FILE *fp);
                
void print_image(int num_rows, int num_cols, int arr[num_rows][num_cols]);

// TODO add the function prototype for count_cells
int count_cells(int num_rows, int num_cols, int arr[num_rows][num_cols]);

int main(int argc, char **argv) {
    // Print a message to stderr and exit with an argument of 1
    // if there are not the right number of parameters, or if
    // there is a second argument that is not -p

    // The following snippet helps you check your arguments.
    // strcmp returns 0 if the strings are equal and
    // you haven't learned about this yet.
    // Notice that this is NOT COMPLETE, but we have given you this
    // much to show you how to check '-p' and print to stderr.
    // Be careful with the array indexing!

    if (argc == 3 && strcmp(argv[2], "-p") != 0) {
        fprintf(stderr, "Usage: count_cells <imagefile.txt> [-p]\n");
        return 1;
    }

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: count_cells <imagefile.txt> [-p]\n");
        return 1;
    }

    int printFlag = 0;
    if (argc == 3 && strcmp(argv[2], "-p") == 0) {
        printFlag = 1;
    }
    
    // TODO read and print images, count cells

    FILE *fp = fopen(argv[1], "r");

    int num_rows, num_cols;
    fscanf(fp, "%d %d", &num_rows, &num_cols);

    int arr[num_rows][num_cols];

    read_image(num_rows, num_cols, arr, fp);

    if (printFlag == 1) {
        print_image(num_rows, num_cols, arr);
    }

    int count = count_cells(num_rows, num_cols, arr);
    printf("Number of Cells is %d\n", count);

    return 0;
}
