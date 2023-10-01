#define MAX_AREA_SIZE 16
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct faculty {
    char *name;
    char area[MAX_AREA_SIZE];
    int num_students;
};


void add_grad_student(struct faculty *p) {
    (p->num_students)++;  // Note: due to C precedence rules, the parentheses are optional
}


int main() {
    // Declare a struct faculty named p1.
    struct faculty p1;

    p1.name = "Roger Grosse";  // Note: this is okay if we assume p1.name will be read-only;
                               // otherwise, use malloc!
    strcpy(p1.area, "ML");
    p1.num_students = 11;

    struct faculty *p2_pt;
    p2_pt = malloc(sizeof(struct faculty));
    if (p2_pt == NULL) {
        perror("malloc");  // Look up the documentation for perror
        return 1;
    }

    p2_pt->name = "Sheila McIlraith";
    strcpy(p2_pt->area, "KR");
    p2_pt->num_students = 5;

    add_grad_student(&p1);
    add_grad_student(p2_pt);

    return 0;
}
