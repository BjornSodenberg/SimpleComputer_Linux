#ifndef TERMLIB_H
#define TERMLIB_H

#include <stdio.h>
#include <sys/ioctl.h>

enum colors {
	cmd_black,
	cmd_blue,
	cmd_green,
	cmd_cyan,
	cmd_red,
	cmd_magenta,
	cmd_brown,
	cmd_light_blue,
	cmd_default
};

int tl_clrscr        (void);
int tl_gotoXY        (int,int);
int tl_getscreensize (int*,int*);
int tl_setfgcolor    (enum colors);
int tl_setbgcolor    (enum colors);

#endif
