#include <stdio.h>

int main() {
  printf("Line %d: %s compiled on %s at %s.\n", __LINE__, __FILE__, __DATE__, __TIME__);
  return 0;
}
