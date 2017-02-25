#ifdef TERMLIB_H
#define TERMLIB_H

#include <stdio.h>
#include <stdlib.h>

int tl_clrscr(void);
int tl_gotoXY (int,int);
int tl_getscreensize(int*,int*);
int tl_setgcolor(enum);
int tl_setbgcolor(enum);

#endif
