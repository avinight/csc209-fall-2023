#include <stdio.h>

int main() {
    double cm, inches;

    printf("Type a number of centimeters: ");
    scanf("%lf", &cm);

    inches = cm * 0.393701;
    printf("%lf centimeters is %lf inches.\n", cm, inches);

    return 0;
}