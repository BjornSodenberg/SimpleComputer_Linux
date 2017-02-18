#ifndef SCLIB_H
#define SCLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MEMSIZE 100

extern int sc_memory[MEMSIZE];

int sc_memoryInit    ();
int sc_memorySet     (int address, int value);
int sc_memoryGet     (int address, int* value);
int sc_memorySave    (char* filename);
int sc_memoryLoad    (char* filename);
int sc_regInit       (void);
int sc_regSet        (int register, int value);
int sc_regGet        (int register, int* value);
int sc_commandEncode (int command, int operand, int* value);
int sc_commandDecode (int value, int* command, int* operand);

#endif
