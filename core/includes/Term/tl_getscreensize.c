#include "termlib.h"

int tl_getscreensize(int*rows,int*cols){
  struct winsize ws;
  if (!ioctl(1, TIOCGWINSZ, &ws))
  {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
  } else
  {
      return -1;
  }
  return 0;
}
