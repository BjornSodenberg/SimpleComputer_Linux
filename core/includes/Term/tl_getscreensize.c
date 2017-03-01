#include "termlib.h"

int tl_getscreensize(int*rows,int*cols){
  struct winsize sz;

  if(!ioctl(0, TIOCGWINSZ, &sz)){
    *rows = sz.ws_row;
    *cols = sz.ws_col;
    return 0;
  }
  else
    return -1;
}
