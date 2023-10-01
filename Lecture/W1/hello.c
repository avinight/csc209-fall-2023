#include <stdio.h>

int main() {
    char name[30];
    printf("Hello CSC209 students!\n");
    fgets(name, 30, stdin);
    printf("Hi %s\n", name);
    return 0;
}
