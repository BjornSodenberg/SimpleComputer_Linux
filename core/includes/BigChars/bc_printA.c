#include "bigchrlib.h"

int bc_printA (char* str)
{
  ssize_t len = strlen(str) * sizeof(char);
  write(1, "\E(0", 3);
  if (write(1, str, len) != len)
  {
      return -1;
  }
  write(1, "\E(B", 3);
  return 0;
}
