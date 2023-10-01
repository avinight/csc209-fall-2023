#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Part 3: Implement build_month_list.
char **build_month_list() {
    // Allocate space for the pointer array
    char **month_list = malloc(3 * sizeof(char *));

    // Allocate and initialize space for "January"
    month_list[0] = malloc((strlen("January") + 1) * sizeof(char));
    strcpy(month_list[0], "January");

    // Allocate and initialize space for "February"
    month_list[1] = malloc((strlen("February") + 1) * sizeof(char));
    strcpy(month_list[1], "February");

    // Allocate and initialize space for "March"
    month_list[2] = malloc((strlen("March") + 1) * sizeof(char));
    strcpy(month_list[2], "March");

    // Warning: this version will compile, but (may) result in a segmentation fault
    // in the truncation code at the end of main.
    // month_list[0] = "January";
    // month_list[1] = "February";
    // month_list[2] = "March";

    return month_list;
}


int main() {
    // Part 1: Declare and initialize first, second, and third.
    char first[7] = "Monday";
    char *second = "Tuesday";
    char *third = malloc((strlen("Wednesday" + 1)) * sizeof(char));
    strcpy(third, "Wednesday");
    // Note: third = "Wednesday"; just assigns a new pointer value to
    // third; it doesn't "copy" the characters from "Wednesday" into the
    // heap memory.

    printf("%s %s %s\n", first, second, third);

    // Part 2: Declare and initialize string_list.
    char *string_list[3];
    string_list[0] = first;
    string_list[1] = second;
    string_list[2] = third;

    printf("%s %s %s\n", string_list[0], string_list[1], string_list[2]);

    // For part 3: Once you've implemented build_month_list, uncomment this code.
    char **months = build_month_list();
    for (int i = 0; i < 3; i++) {
        printf("%s ", months[i]);
    }
    printf("\n");

    for (int i = 0; i < 3; i++) {
        months[i][3] = '\0';
        printf("%s ", months[i]);
    }
    printf("\n");

    // Good practice to free all malloc'd memory!
    free(months[0]);
    free(months[1]);
    free(months[2]);
    free(months);
    free(third);

    return 0;
}
