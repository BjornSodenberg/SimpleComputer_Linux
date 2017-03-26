CC = gcc
CFLAGS = -g
LFLAGS = -L./core/lib/

.PHONY: clean

all: sclib.a termlib.a bigcharlib.a Tests 

sclib.a:
	cd core/includes/SC/ && make all

termlib.a:
	cd core/includes/Term/ && make all

bigcharlib.a:
	cd core/includes/BigChars/ && make all

Tests:
	cd tests && make all

clean:
	cd core/includes/SC/ && make clean
	cd core/includes/Term/ && make clean
	cd core/includes/BigChars && make clean
	cd core/lib && rm -f *.a
	cd tests && make clean
	cd src && rm -f memory
