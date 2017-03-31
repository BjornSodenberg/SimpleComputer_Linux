CC = gcc
CFLAGS = -g
INCLUDE = -I../core/includes/SC -I../core/includes/Term \
-I../core/includes/BigChars -I../core/includes/ReadKey
LIBS = -L../core/lib
LFLAG = -lsclib -ltermlib -lbigcharlib -lreadkeylib

.PHONY: clean

all:initConsole.o Anthill

Anthill:
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o Anthill \
																Anthill.c $(LFLAG)

initConsole.o:initConsole.c initConsole.h
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -c initConsole.c

clean:
	rm -f *.o
