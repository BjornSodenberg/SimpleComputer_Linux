CC = gcc
CFLAGS = -g
INCLUDE = -I../core/includes
LIBS = -L../core/lib
LFLAG = -lsclib -ltermlib

.PHONY: clean

all: SimpleComputer_test

SimpleComputer_test:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o SimpleComputer_test SimpleComputer_test.c $(LFLAG)

clean:
	rm -f SimpleComputer_test
