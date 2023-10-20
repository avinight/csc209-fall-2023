#include <stdio.h>
#include <string.h>

struct student {
    char first_name[20];
    char last_name[20];
    int year;
    float gpa;
};

/* This version of change() operates on a *copy* of struct s,
   not the original. This means that the print statement in main
   will print:
       first name if "Jo"
       GPA is 2.1
   ..since the original good_student is not modified by change().

====

void change(struct student s) {
    s.gpa = 4.0;
    strcpy(s.first_name, "Adam");
}
*/

/* Changes the values of a struct student's members. 
   This function operates on the *original* struct, rather
   than on a copy of the struct. */
void change(struct student *s) {
    strcpy((*s).first_name, "Adam");
    (*s).gpa = 4.0;
}

int main() {
    struct student good_student;
 
    strcpy(good_student.first_name, "Jo"); 
    good_student.gpa = 2.1;

    // Passing address of good_student:
    change(&good_student);
    
    printf("first name is %s\n",
                good_student.first_name);
    printf("GPA is %f\n", good_student.gpa);
  
    return 0;
}








