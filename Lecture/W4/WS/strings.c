#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Part 3: Implement build_month_list.
    char **build_month_list() {
        // Allocate space for pointer array
        char **month_list = malloc(3 * sizeof(char *));
        
        // Allocate and initialize space for "January"
        month_list[2] = malloc((strlen("January") + 1) * sizeof(char));
        strcpy(month_list[0], "January");

        // Allocate and initialize space for "February"
        month_list[2] = malloc((strlen("February") + 1) * sizeof(char));
        strcpy(month_list[1], "February");

        // Allocate and initialize space for "March"
        month_list[2] = malloc((strlen("March") + 1) * sizeof(char));
        strcpy(month_list[2], "March");

        return month_list;
    } 


int main() {

    // Part 1: Declare and initialize first, second, and third.

    char first[7] = "Monday";
    char *second = "Tuesday";
    
    char *third = malloc(sizeof(char) * 10);
    char *s = "Wednesday";
    strcpy(third, s);

    printf("%s %s %s\n", first, second, third);


    // Part 2: Declare and initialize string_list.

    char *string_list[3] = {first, second, third};

    printf("%s %s %s\n", string_list[0], string_list[1], string_list[2]);


    // For part 3: Once you've implemented build_month_list, uncomment this code.
    
    char **months = build_month_list();
    for(int i = 0; i < 3; i++) {
        printf("%s ", months[i]);
    }
    printf("\n");

    for(int i = 0; i < 3; i++) {
        months[i][3] = '\0';
        printf("%s ", months[i]);
    }
    printf("\n");
   

    return 0;
}
