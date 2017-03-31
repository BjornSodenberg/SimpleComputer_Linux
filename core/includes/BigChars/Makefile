CC = gcc
CFLAGS = -g -Wall
SRCS = bc_bigcharread.c bc_bigcharwrite.c bc_box.c bc_getbigcharpos.c \
bc_printA.c bc_printbigchar.c bc_setbigcharpos.c
OBJS = $(SRCS:.c=.o)
INCLUDE = -I../Term
.PHONY: clean

all:
	$(CC) $(INCLUDE) $(CFLAGS) -c $(SRCS)
	ar rvs ../../lib/libbigcharlib.a $(OBJS)

clean:
	rm -f *.o
