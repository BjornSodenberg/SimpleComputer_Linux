#include "bigchrlib.h"

int bc_setbigcharpos ( int*big, int x, int y, int value )
{
  if (x < 0 || x > 7 || y < 0 || y > 7 || value > 1 || value < 0)
      return 1;
  int part = x / 4;
  x %= 4;
  if (value)
      big[part] |= (1 << (8 * x + y));
  else big[part] &= ~(1 << (8 * x + y));
  return 0;
}
