#include <stdio.h>

#define SUPERVISOR(regular) regular + 5
int main() {
    int regular_pay = 20;
    int hours_worked = 10;
    printf("pay is %d\n", (hours_worked * SUPERVISOR(regular_pay)));
    //  rest omitted
}