#include <stdio.h>
int main() {
    count = 5
    int ages[count] = {1, 4, 3, 2, 5};
    int i;
    int oldest = ages[0];
    int second_oldest = ages[1];
    for (i = 0; i < count; i++) {
      if (ages[i] >= second_oldest) {
        second_oldest = ages[i];
        }
        if (ages[i] >= oldest) {
          oldest = ages[i];
          second_oldest = oldest;
        }
    }
    printf("%d\n", second_oldest);
    return -1;
  }
}

