CC = gcc
CFLAGS = -g
SRCS = tl_clrscr.c \
tl_getscreensize.c tl_gotoXY.c \
tl_setfgcolor.c tl_setbgcolor.c
OBJS = $(SRCS:.c=.o)

.PHONY: clean

all:
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rvs ../../lib/libtermlib.a $(OBJS)

clean:
	rm -f *.o
