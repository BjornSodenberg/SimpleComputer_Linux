#ifndef CMD_H
#define CMD_H

#include "includes/Term/termlib.h"

int console_init(int X,int Y, enum colors fgcolor, enum colors bgcolor) {
  tl_clrscr();
  tl_setbgcolor(bgcolor);
  tl_setfgcolor(fgcolor);
  tl_gotoXY(X,Y);
}

#endif
