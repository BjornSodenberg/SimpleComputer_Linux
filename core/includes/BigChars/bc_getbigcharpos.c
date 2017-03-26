#include "bigchrlib.h"

int bc_getbigcharpos ( int*big, int x, int y, int* value )
{
  if (x < 0 || x > 7 || y < 0 || y > 7)
      return -1;
  short int part = x / 4;
  x %= 4;
  if (big[part] & (1 << (8 * x + y)))
  {
      *value = 1;
  } else *value = 0;
  return 0;
}
