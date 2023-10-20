#include <stdio.h>

int main() {

  #ifdef DEBUG
  printf("Running in debug mode at level %d\n", DEBUG);
  #endif

  return 0;
}
