#include <stdio.h>

#define GREATER(a, b) ((a) > (b) ? (a) : (b))

//  For Step 4, remove macro and add this inline function
//  static inline int GREATER(int a, int b) {
//     return a > b ? a : b;
//  }

int main() {
    int x = 2;
    int y = 1;

//  For Step 2, add this line 
//  y = y + 1;                         

    printf("%d\n", GREATER(x, y));     // Original code Step 1

//  For Step 3,  replace the Step 1 line with this
//               what goes wrong now? 
//  printf("%d\n", GREATER(x, ++y));   

    return 0;
}

