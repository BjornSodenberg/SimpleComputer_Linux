CC = gcc
CFLAGS = -g
INCLUDE = -I../core/includes/SC -I../core/includes/Term -I../core/includes/BigChars
LIBS = -L../core/lib
LFLAG = -lsclib -ltermlib -lbigcharlib

.PHONY: clean

all: SimpleComputer_test Term_test Console_init

SimpleComputer_test:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o SimpleComputer_test \
																SimpleComputer_test.c $(LFLAG)

Term_test:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o Term_test \
																Term_test.c $(LFLAG)

Console_init:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o Console_init \
																Console_init.c -lbigcharlib -ltermlib

clean:
	rm -f SimpleComputer_test Term_test Console_init
