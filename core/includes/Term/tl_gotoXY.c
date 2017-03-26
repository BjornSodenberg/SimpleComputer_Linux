#include "termlib.h"

int tl_gotoXY(int X,int Y) {
  char go[30];
  sprintf(go, "\E[%d;%dH", X, Y);
  ssize_t len = strlen(go) * sizeof(char);
  if (write(1, go, len) < len)
  {
      return -1;
  }
  return 0;
}
