#include "termlib.h"

int tl_clrscr(void) {
  char *clear;
  clear = "\E[H\E[2J";
  ssize_t len = strlen(clear) * sizeof(char);
  if (write(1, clear, strlen(clear)) < len)
  {
      return -1;
  }
  return 0;
}
