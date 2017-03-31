#ifndef __GUARD_MYREADKEY_H
#define __GUARD_MYREADKEY_H

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

enum keys {
	l_key,
	s_key,
	r_key,
	t_key,
	i_key,
	f5_key,
	f6_key,
	up_key,
	down_key,
	left_key,
	right_key,
	enter_key
};

int rk_readkey(enum keys *key);
int rk_termsave();
int rk_termrestore();
int rk_termregime(int regime, int vtime, int vmin, int echo, int sigint);

#endif /* __GUARD_MYREADKEY_H */
