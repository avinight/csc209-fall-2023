#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"

/* The last filter is used to scale an existing image. 
 * It takes one command-line argument scale_factor, which must be an integer greater than 0. 
 * The image produced by this filter should be the same as the original image, except its width and height 
 * are multiplied by the provided scale factor. 
 *
 * You may assume this command-line argument is always provided, 
 * and is always valid (no error-checking is required for this).
 * 
 * The pixel at position (i, j) in the scaled image should equal the pixel at position (i / scale_factor, j / scale_factor) 
 * in the original image. Note that this is integer division, which rounds down. 
 * (This is the simplest form of scaling, and it doesn’t produce very smooth-looking images. 
 * There are more complex algorithms for scaling you’ll learn about in courses like CSC320.)
 * 
 * In order for the output bitmap to be valid, you’ll need to update three parts of the bitmap header before writing it to stdout: 
 * the image width, image height, and the total file size. Note that the header’s size does not change with this transformation, 
 * and so you can compute the new file size by adding the header size to the total space required to store all the pixels in the image.
 */
void scale_filter(Bitmap *bmp) {
    int scale_factor = bmp->scale_factor;
    Pixel *row = malloc(bmp->width * sizeof(Pixel));
    if (row == NULL) {
        fprintf(stderr, "Failed to allocate memory for pixel row.\n");
        return;
    }

    for (int j = 0; j < bmp->height; j++) {
        // Read one row from the input
        if (fread(row, sizeof(Pixel), bmp->width, stdin) != bmp->width) {
            fprintf(stderr, "Failed to read pixel row from file.\n");
            free(row);
            return;
        }

        // Write this row to the output scale_factor times
        for (int s_j = 0; s_j < scale_factor; s_j++) {
            for (int i = 0; i < bmp->width; i++) {
                // Write each pixel in the row to the output scale_factor times
                for (int s_i = 0; s_i < scale_factor; s_i++) {
                    if (fwrite(&row[i], sizeof(Pixel), 1, stdout) != 1) {
                        fprintf(stderr, "Failed to write pixel to file.\n");
                        free(row);
                        return;
                    }
                }
            }
        }
    }
    free(row);
}

int main(int argc, char *argv[]) {
    // Run the filter program with scale_filter to process the pixels.
    // You shouldn't need to change this implementation.
    if (argc != 2) {
        fprintf(stderr, "Usage: %s scale_factor\n", argv[0]);
        exit(1);
    }
    int scale_factor = strtol(argv[1], NULL, 10);
    run_filter(scale_filter, scale_factor);
    return 0;
}