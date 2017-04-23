CC = gcc
CFLAGS = -g -Wall
LFLAGS = -L./core/lib/

.PHONY: clean

all: sclib.a termlib.a bigcharlib.a readkeylib.a Tests SimpleComputer

sclib.a:
	cd core/includes/SC/ && make all

termlib.a:
	cd core/includes/Term/ && make all

bigcharlib.a:
	cd core/includes/BigChars/ && make all

readkeylib.a:
	cd core/includes/ReadKey/ && make all

Tests:
	cd bin/tests && make all

SimpleComputer:
	cd bin/ && make all

clean:
	cd core/includes/SC/ && make clean
	cd core/includes/Term/ && make clean
	cd core/includes/BigChars && make clean
	cd core/includes/ReadKey && make clean
	cd core/lib && rm -f *.a
	cd bin/ && make clean
	cd bin/tests && make clean
	cd src && rm -f memory
	rm -f SimpleComputer
