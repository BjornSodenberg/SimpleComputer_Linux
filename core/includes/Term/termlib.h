#ifndef TERMLIB_H
#define TERMLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory.h>

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
