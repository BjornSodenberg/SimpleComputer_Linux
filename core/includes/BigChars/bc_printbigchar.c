#include "bigchrlib.h"

int bc_printbigchar ( int*big, int x, int y,
			enum colors fg, enum colors bg )
{
	tl_setbgcolor(bg);
	tl_setfgcolor(fg);
	for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
					tl_gotoXY(x + i, y + j);
					int value;
					bc_getbigcharpos(big, i, j, &value);
					if (!value)
							write(1, " ", sizeof(char));
					else
							bc_printA("a");
			}
			write(1, "\n", sizeof(char));
	}
	return 0;
}
