CC = gcc
CFLAGS = -g
INCLUDE = -I../core/includes
LIBS = -L../core/lib
SRCS = SimpleComputer.c
OBJS = $(SRCS:.c=.o)

.PHONY: clean

all:
	$(CC) $(INCLUDE) $(LIBS) $(CFLAGS) -o ../SimpleComputer_Linux $(SRCS) -lsclib

clean:
	rm -f ../SimpleComputer_Linux
