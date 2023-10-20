#include <stdio.h>
#include <stdlib.h>

// some programmers argue that this is a good idea
typedef unsigned int age_t; 
typedef unsigned int shoe_size_t;

void print_boot_size(shoe_size_t shoe_size) { 
    printf("Boot size:%d\n", shoe_size + 2);
}

struct student {
    char first_name[20];
    char last_name[20];
    int year;
    float gpa;
};
typedef struct student Student;

/* We could also have done it this way
typedef struct {
    char first_name[20];
    char last_name[20];
    int year;
    float gpa;
} Student;
*/

int main() {

    print_boot_size(7);
    // but the compiler won't object if we do this
    // so other programmers argue that using typedef here is not helpful
    age_t driving_age = 16;
    print_boot_size(driving_age);


    // Most agree that using typedef with structs is helpful
    Student s;
    Student *p;

    s.year = 2;
    p = malloc(sizeof(Student));

    return 0;
}

