#include <stdio.h>

int main() {
    int i;
    i = 5;
    printf("Value of i: %d\n", i);
    printf("Address of i: %p\n", &i);
    
    // declare a pointer pt that will point to an int
    int *pt;
    // set pt to hold the address of i
    pt = &i;
    
    // print the value of the pointer (which is the address of i)
    printf("Value of pt: %p\n", pt);
    // the pointer itself has an address, print that
    printf("Address of pt: %p\n", &pt);

    // print the value in the address that is itself stored in pt
    printf("Value pointed to by pt: %d\n", *pt);
    return 0;
}
