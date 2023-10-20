#include <stdio.h>
#include <string.h>

int main() {
    // Note that "struct" is required whenever we declare
    // a variable of a structure type:
    struct student {
        // Members of struct student:
        char first_name[20];
        char last_name[20];
        int year;
        float gpa;
    };

    // good_student is of type "struct student"
    struct student good_student;
  
    // Initialize the members of the struct using dot notation:
    strcpy(good_student.first_name, "Jo");
    strcpy(good_student.last_name, "Smith");
    good_student.year = 2;
    good_student.gpa = 3.2;
  
    // Print the values of good_student's members:
    printf("Name: %s %s\n",
           good_student.first_name, good_student.last_name);
    printf("Year: %d. GPA: %.2f\n", good_student.year, good_student.gpa);
  
    return 0;
}





