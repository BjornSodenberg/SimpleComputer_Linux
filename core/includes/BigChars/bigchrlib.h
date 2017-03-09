#ifndef BIGCHRLIB_H
#define BIGCHRLIB_H

#include "../Term/termlib.h"
// TODO enter_alt_charset_mode \E[11m
// TODO exit_alt_charset_mode \E[10m
// TODO acs_chars +\020\054\021-\030.^Y0\333`\004a\261f\370g\361h\260i\316j\331k\277l\332m\300n\305o~p\304q\304r\304s_t\303u\264v\301w\302x\263y\363z\362{\343|\330}\234~\376

#define BOXCHAR_REC 'a'
#define BOXCHAR_BR "j"
#define BOXCHAR_BL "m"
#define BOXCHAR_TR "k"
#define BOXCHAR_TL "l"
#define BOXCHAR_VERT "x"
#define BOXCHAR_HOR "q"

int bc_printA        (char* str);
int bc_box           (int x1,int y1,int x2,int y2);
int bc_printbigchar  (int[2],int x, int y, enum color, enum color);
int bc_setbigcharpos (int* big, int x,int y ,int value);
int bc_getbigcharpos (int*big,int x,int y ,int* value);
int bc_bigcharwrite  (int fd,int*big,int count);
int bc_bigcharread   (int fd,int*big,int need_count,int* count);

#endif
