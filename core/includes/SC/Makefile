CC = gcc
CFLAGS = -g
SRCS = sc_memoryInit.c sc_memorySave.c sc_memoryGet.c \
 sc_memoryLoad.c sc_memorySet.c  sc_regInit.c sc_regSet.c sc_regGet.c \
 sc_commandDecode.c sc_commandEncode.c int_cmp.c const.c
OBJS = $(SRCS:.c=.o)

.PHONY: clean

all:
	$(CC) $(CFLAGS) -c $(SRCS)
	ar rvs ../../lib/libsclib.a $(OBJS)

clean:
	rm -f *.o
