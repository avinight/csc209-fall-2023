#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"


/*
 * Main filter loop.
 * This function is responsible for doing the following:
 *   1. Read in pixels one at a time (because greyscale is a pixel-by-pixel transformation).
 *   2. Compute the average of the red, green, and blue values.
 *   3. Set the red, green, and blue values to the average.
 *   4. Write the pixel back out.
 *
 * Note that this function should allocate space only for a single Pixel;
 * do *not* store more than one Pixel at a time, it isn't necessary here!
 */
void greyscale_filter(Bitmap *bmp) {
    // TODO: Complete this function.
    Pixel *p = malloc(sizeof(Pixel));
    if (p == NULL) {
        fprintf(stderr, "Failed to allocate memory for pixel.\n");
        return;
    }
    for (int i = 0; i < bmp->height; i++) {
        for (int j = 0; j < bmp->width; j++) {
            if (fread(p, sizeof(Pixel), 1, stdin) != 1) {
                fprintf(stderr, "Failed to read pixel from file.\n");
                free(p);
                return;
            }
            unsigned char average = (p->blue + p->green + p->red) / 3;
            p->blue = average;
            p->green = average;
            p->red = average;
            if (fwrite(p, sizeof(Pixel), 1, stdout) != 1) {
                fprintf(stderr, "Failed to write pixel to file.\n");
                free(p);
                return;
            }
        }
    }
    free(p);
}

int main() {
    // Run the filter program with greyscale_filter to process the pixels.
    // You shouldn't need to change this implementation.
    run_filter(greyscale_filter, 1);
    return 0;
}