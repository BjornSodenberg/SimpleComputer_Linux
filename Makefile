CC = gcc
CFLAGS = -g
LFLAGS = -L./core/lib/

.PHONY: clean

all: sclib.a SimpleComputer

SimpleComputer:
	cd src && make all

sclib.a:
	cd core/includes && make all

clean:
	cd core/includes && make clean
	cd core/lib && rm -f *.a
	cd src && make clean
	rm -f *.bin SimpleComputer_Linux
