#include "bigchrlib.h"

int bc_bigcharread ( int fd, int* big, int need_count, int* count)
{
  for (*count = 0; (*count < need_count * 2); *count += 1)
      if (read(fd, &big[*count], sizeof(int)) == -1)
          return 1;

  return 0;
}
