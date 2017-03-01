#include "termlib.h"

int tl_clrscr(void) {
  printf("\E[H\E[2J");
  return 0;
}
