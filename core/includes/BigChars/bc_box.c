#include "bigchrlib.h"

int bc_box ( int x1, int y1, int x2, int y2 ) {
  for (int i = 0; i < x2; i++)
  {
      for (int j = 0; j < y2; j++)
      {
          tl_gotoXY(x1 + i, y1 + j);

          //corners
          if (i == 0 && j == 0)
              bc_printA("l");
          else if (i == 0 && j == y2 - 1)
              bc_printA("k\n");
          else if (i == x2 - 1 && j == 0)
              bc_printA("m");
          else if (i == x2 - 1 && j == y2 - 1)
              bc_printA("j\n");
          else if ( (i == 0 || i == x2 - 1) && (j > 0 && j < y2) ) // horizontal line
              bc_printA("q");
          else if ( (i > 0 && i < x2) && (j == 0 || j == y2 -1)) // vertical line
              bc_printA("x");
          else
              write(1, " ", sizeof(char));
      }
  }
  return 0;
}
