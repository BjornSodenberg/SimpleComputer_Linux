#include "termlib.h"

int tl_gotoXY(int X,int Y) {
  int rows = 0,cols= 0;
  tl_getscreensize(&rows,&cols);
  if((Y < rows) && (X < cols) & (Y >= 0) && (X >= 0)) {
    printf("\E[%d;%dH",Y ,X );
    return 0;
  }
  return -1;
}
