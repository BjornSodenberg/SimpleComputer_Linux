#include "bigchrlib.h"

int bc_box(int x1,int y1,int x2,int y2) {
  int temp;
  int maxX, maxY;
  if(x1 < x2) {
    temp = x1,x1 = x2;
    x2 = temp;
  }

  if(y1 < y2) {
    temp = y1;
    y1 = y2;
    y2 = temp;
  }
  tl_getscreensize(&maxY,&maxX);
  if ((x1 < 0) || (y1 < 0) || (x1 > maxX) || (y2 > maxY)) {
    return -1;
  }

  lt_gotoXY(x1,y1);
  bc_printA(BIGCHAR_VERT);
  

}
