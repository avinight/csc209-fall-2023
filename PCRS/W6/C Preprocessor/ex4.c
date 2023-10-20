#include <stdio.h>

#if __APPLE__
const char OS_STR[] = "OS/X";
#elif __gnu_linux__
const char OS_STR[] = "gnu/linux";
#else
const char OS_STR[] = "unknown";
#endif

int main() {
  printf("Compiled on %s\n", OS_STR);
  return 0;
}
