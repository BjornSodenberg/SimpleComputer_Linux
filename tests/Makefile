CC = gcc
CFLAGS = -g
INCLUDE = -I../core/includes
LIBS = -L../core/lib

.PHONY: clean

all: SimpleComputer_test

SimpleComputer_test:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o SimpleComputer_test SimpleComputer_test.c -lsclib

clean:
	rm -f SimpleComputer_test
	rm -f memory
