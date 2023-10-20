#include <stdio.h>

int main() {
  printf("Compiled on linux? %d\n", __gnu_linux__);
  printf("Compiled on OS X? %d\n", __APPLE__);
  return 0;
}
