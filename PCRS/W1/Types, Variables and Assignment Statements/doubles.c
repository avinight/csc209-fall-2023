#include <stdio.h>

int main() {
    int temperature = 32;
    temperature = 98.1;     // the ".1" is discarded and 
                            // the value of "temperature"
                            // is now 98

    // The video uses "temperature", but we can't re-declare
    // a variable in a program, so we'll use "temp" instead.
    double temp = 32;
    temp = 98.6;

    // The following evaluates to 2 because the operation
    // 9 / 4 gives the *integer* result of 2.
    double quotient = 9 / 4;

    // The modulo operator "%" gives the remainder of the
    // division:
    int modulo = 9 % 4;

    return 0;
}