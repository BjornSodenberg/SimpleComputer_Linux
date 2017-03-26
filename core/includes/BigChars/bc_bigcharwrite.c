#include "bigchrlib.h"

int bc_bigcharwrite ( int fd, int* big, int count )
{
  for (int i = 0; i < count * 2; i++)
      if (write(fd, &big[i], sizeof(int)) == -1)
         return 1;
  return 0;
}
