#include <stdio.h>

#ifdef __APPLE__
const char OS_STR[] = "OS/X";
#elif defined(__gnu_linux__)
const char OS_STR[] = "gnu/linux";
#else
const char OS_STR[] = "unknown";
#endif

int main() {
  printf("Compiled on %s\n", OS_STR);
  return 0;
}
