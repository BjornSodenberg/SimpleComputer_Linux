CC = gcc
CFLAGS = -g
LFLAGS = -L./core/lib/

.PHONY: clean

all: sclib.a SimpleComputer_test

sclib.a:
	cd core/includes/SC/ && make all

SimpleComputer_test:
	cd tests && make all

clean:
	cd core/includes/SC/ && make clean
	cd core/lib && rm -f *.a
	cd tests && make clean
	cd src && rm -f memory
