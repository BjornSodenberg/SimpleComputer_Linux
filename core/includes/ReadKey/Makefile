CC = gcc
CFLAGS = -g -Wall
SRCS = rk_readkey.c rk_termregime.c rk_termrestore.c rk_termsave.c
OBJS = $(SRCS:.c=.o)
.PHONY: clean

all:
	$(CC) $(INCLUDE) $(CFLAGS) -c $(SRCS)
	ar rvs ../../lib/libreadkeylib.a $(OBJS)

clean:
	rm -f *.o
