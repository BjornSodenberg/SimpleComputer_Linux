#include "bigchrlib.h"

int bc_box ( int x1, int y1, int x2, int y2 ) {
  for (int i = 0; i < x2; i++)
  {
      for (int j = 0; j < y2; j++)
      {
          tl_gotoXY(x1 + i, y1 + j);

          if (i == 0 && j == 0)
              bc_printA(BOXCHAR_TL);
          else if (i == 0 && j == y2 - 1)
              {bc_printA(BOXCHAR_TR);bc_printA("\n");}
          else if (i == x2 - 1 && j == 0)
              bc_printA(BOXCHAR_BL);
          else if (i == x2 - 1 && j == y2 - 1)
              {bc_printA(BOXCHAR_BR);bc_printA("\n");}
          else if ( (i == 0 || i == x2 - 1) && (j > 0 && j < y2) )
              bc_printA(BOXCHAR_HOR);
          else if ( (i > 0 && i < x2) && (j == 0 || j == y2 -1))
              bc_printA(BOXCHAR_VERT);
      }
  }
  return 0;
}
