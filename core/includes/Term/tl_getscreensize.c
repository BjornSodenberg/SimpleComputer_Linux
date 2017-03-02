#include "termlib.h"

int tl_getscreensize(int*rows,int*cols){
  struct winsize size;

  if(!ioctl(0, TIOCGWINSZ, &size)){
    *rows = size.ws_row;
    *cols = size.ws_col;
    return 0;
  }
  else
    return -1;
}
