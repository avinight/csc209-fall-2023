#include <stdio.h>
    
/* Reads the image from the open file fp into the two-dimensional array arr 
 * num_rows and num_cols specify the dimensions of arr
 */
void read_image(int num_rows, int num_cols, 
                int arr[num_rows][num_cols], FILE *fp) {
    int i, j;
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            fscanf(fp, "%d", &arr[i][j]);
        }
    }    
}

/* Print to standard output the contents of the array arr */
void print_image(int num_rows, int num_cols, int arr[num_rows][num_cols]) {
    int i, j;
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

/* TODO: Write the count_cells function */
int flood_fill(int x, int y, int num_rows, int num_cols, int arr[num_rows][num_cols], int seen[num_rows][num_cols]) {
    // Check that the pixel exists within the array and that it has not already been seen
    if (x < 0 || y < 0 || x >= num_rows || y >= num_cols || seen[x][y] != 0) {
        return 0;
    }

    // Mark that this pixel has been seen
    seen[x][y] = 1;

    // Perform flood_fill on each of the cardinal directions and return 1 to count one cell
    if (arr[x][y] == 255) {
        flood_fill(x, y + 1, num_rows, num_cols, arr, seen);
        flood_fill(x + 1, y, num_rows, num_cols, arr, seen);
        flood_fill(x, y - 1, num_rows, num_cols, arr, seen);
        flood_fill(x - 1, y, num_rows, num_cols, arr, seen);
        return 1;
    }
    // If a cell is not found return 0
    return 0;
}

int count_cells(int num_rows, int num_cols, int arr[num_rows][num_cols]) {
    int cell_count = 0;

    // Create a boolean array to track of seen pixels
    int seen[num_rows][num_cols];

    // Initialize all pixels as unseen (false)
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            seen[i][j] = 0;
        }
    }

    // Recursion: add to cell_count the total number of cells found
    int i, j;
    for (i = 0; i < num_rows; i++) {
        for (j = 0; j < num_cols; j++) {
            cell_count += flood_fill(i, j, num_rows, num_cols, arr, seen);
        }
    }
    return cell_count;
}
