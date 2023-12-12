#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"


/*
 * Main filter loop.
 *
 * row0, row1, and row2 are interpreted as Pixel arrays of length 3.
 * Together, they represent the three rows of a 3-by-3 pixel grid
 * whose middle pixel is the one being transformed.
 *
 * These functions return the transformed pixel value of the middle pixel
 * when applying the corresponding transformation (a gaussian blur or
 * an edge detection operation), using the pixel values in the 3-by-3 grid.
 *
 * You aren't responsible for the calculations themselves, only for calling
 * these functions properly on pointers representing the 3-by-3 grids.
 *
 * Note that these functions should be called *once per pixel in the image*;
 * the returned Pixel values can be immediately written to stdout.
 * This function is responsible for doing the following:
 *   1. Read in pixels.
 *   2. Apply the Gaussian blur transformation.
 *   3. If the pixel is a boundary pixel, make every “edge” pixel have the exact same transformed value as its “inner” neighbour.
 *   3. Write the pixel back out.
 *
 */
void gaussian_blur_filter(Bitmap *bmp) {
    // TODO: Complete this function.
    
    Pixel *p = malloc(sizeof(Pixel) * bmp->width);
    if (p == NULL) {
        fprintf(stderr, "Failed to allocate memory for pixel.\n");
        return;
    }

    // Allocate memory for the rows
    Pixel *frow0 = malloc(sizeof(Pixel) * bmp->width);
    Pixel *frow1 = malloc(sizeof(Pixel) * bmp->width);
    Pixel *frow2 = malloc(sizeof(Pixel) * bmp->width);
    if (frow0 == NULL || frow1 == NULL || frow2 == NULL) {
        fprintf(stderr, "Failed to allocate memory for rows.\n");
        free(p);
        return;
    }
    
    // Read in the first two rows
    if (fread(frow1, sizeof(Pixel), bmp->width, stdin) != bmp->width || fread(frow2, sizeof(Pixel), bmp->width, stdin) != bmp->width) {
        fprintf(stderr, "Failed to read rows from file.\n");
        free(p);
        free(frow0);
        free(frow1);
        free(frow2);
        return;
    }

    // Allocate memory for the 3x3 grid
    Pixel *row0 = malloc(sizeof(Pixel) * 3);
    Pixel *row1 = malloc(sizeof(Pixel) * 3);
    Pixel *row2 = malloc(sizeof(Pixel) * 3);
    if (row0 == NULL || row1 == NULL || row2 == NULL) {
        fprintf(stderr, "Failed to allocate memory for 3x3 grid.\n");
        free(p);
        free(frow0);
        free(frow1);
        free(frow2);
        return;
    }

    // Create a buffer to store the transformed values
    Pixel *buffer = malloc(sizeof(Pixel) * bmp->width * 2);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for buffer.\n");
        free(p);
        free(frow0);
        free(frow1);
        free(frow2);
        free(row0);
        free(row1);
        free(row2);
        return;
    }

    // Initialize the buffer size
    int bufferSize = 0;

    // Loop through the pixels
    for (int j = 0; j < bmp->height; j++) {
        for (int i = 0; i < bmp->width; i++) {
            // Populate the 3x3 grid
            if (j == 0) {
                row0[0] = frow1[max(0, min(bmp->width - 1, i - 1))];
                row0[1] = frow1[max(0, min(bmp->width - 1, i))];
                row0[2] = frow1[max(0, min(bmp->width - 1, i + 1))];
            } else {
                row0[0] = frow0[max(0, min(bmp->width - 1, i - 1))];
                row0[1] = frow0[max(0, min(bmp->width - 1, i))];
                row0[2] = frow0[max(0, min(bmp->width - 1, i + 1))];
            }
            if (j == bmp->height - 1) {
                row2[0] = frow1[max(0, min(bmp->width - 1, i - 1))];
                row2[1] = frow1[max(0, min(bmp->width - 1, i))];
                row2[2] = frow1[max(0, min(bmp->width - 1, i + 1))];
            } else {
                row2[0] = frow2[max(0, min(bmp->width - 1, i - 1))];
                row2[1] = frow2[max(0, min(bmp->width - 1, i))];
                row2[2] = frow2[max(0, min(bmp->width - 1, i + 1))];
            }
        
            row1[0] = frow1[max(0, min(bmp->width - 1, i - 1))];
            row1[1] = frow1[max(0, min(bmp->width - 1, i))];
            row1[2] = frow1[max(0, min(bmp->width - 1, i + 1))];

            // Apply the filter
            *p = apply_gaussian_kernel(row0, row1, row2);
            
            // Copy the transformed value into the buffer
            memcpy(buffer + bufferSize, p, sizeof(Pixel));

            // Increment the buffer size
            bufferSize += 1;

            // If the buffer is filled
            if (bufferSize == bmp->width * 2) {
                // Handle the boundary pixels in the buffer
                for (int y = 0; y < 2; y++) {
                    for (int x = 0; x < bmp->width; x++) {
                        if (j == 1 && y == 0) {
                            buffer[x] = buffer[bmp->width + max(1, min(bmp->width - 2, x))];
                        }
                        if (j == bmp->height - 1 && y == 1) {
                            buffer[(y * bmp->width) + x] = buffer[max(1, min(bmp->width - 2, x))];
                        }
                        if (x == 0 && j != 1 && j != bmp->height - 1) {
                            buffer[y * bmp->width + x] = buffer[y * bmp->width + x + 1];
                        }
                        if (x == bmp->width - 1 && j != 1 && j != bmp->height - 1) {
                            buffer[y * bmp->width + x] = buffer[y * bmp->width + x - 1];
                        }
                    }
                }
                // Print the first row in the buffer
                fwrite(buffer, sizeof(Pixel), bmp->width, stdout);

                // Shift the second row in the buffer to the first row
                memmove(buffer, buffer + bmp->width, bmp->width * sizeof(Pixel));

                // Reset the buffer size
                bufferSize = bmp->width;
            }
        }

        // Copy row 1 into row 0
        memcpy(frow0, frow1, sizeof(Pixel) * bmp->width);

        // Copy row 2 into row 1
        memcpy(frow1, frow2, sizeof(Pixel) * bmp->width);

        // Read in the next row
        if (j < bmp->height - 1) {
            fread(frow2, sizeof(Pixel), bmp->width, stdin);
        }
    }
    // Print the remaining pixels in the buffer
    if (bufferSize > 0) {
        fwrite(buffer, sizeof(Pixel), bufferSize, stdout);
    }

    // Free memory
    free(row0);
    free(row1);
    free(row2);
    free(frow0);
    free(frow1);
    free(frow2);
    free(p);
    free(buffer);
}

int main() {
    // Run the filter program with edge_detection_filter to process the pixels.
    // You shouldn't need to change this implementation.
    run_filter(gaussian_blur_filter, 1);
    return 0;
}