CC = gcc
CFLAGS = -g
INCLUDE = -I../core/includes/SC -I../core/includes/Term \
-I../core/includes/BigChars -I../core/includes/ReadKey
LIBS = -L../core/lib
LFLAG = -lsclib -ltermlib -lbigcharlib -lreadkeylib
SRCS = SimpleComputer.c

.PHONY: clean

all:
	$(CC) $(INCLUDE) $(LIBS) $(CFLAGS) -o ../SimpleComputer $(SRCS) $(LFLAG)

clean:
	rm -f ../SimpleComputer memory
