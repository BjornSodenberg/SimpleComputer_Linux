#ifndef SCLIB_H
#define SCLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define reserve_memory 100
#define FLAG_ovrflw 0
#define FLAG_dvsn 1
#define FLAG_outmem 2
#define FLAG_interrupt 3
#define FLAG_cmmd 4
#define FLAG_odd 5

#define ERR_WA -1
#define ERR_OFile -2
#define ERR_FSize -3
#define ERR_UCC -4
#define ERR_AttrBit -5
#define ERR_WF -6

#define BIT_SET(X, Y) (X =((X) | (1 << (Y))))
#define BIT_CLEAR(X, Y) (X = ((X) & ~(1 << (Y))))
#define BIT_CHECK(X, Y) (((X) >> Y) & 1)

extern int sc_memory[reserve_memory];
extern int sc_reg_flags;
extern const int correct_commands[];
extern const int commands_count;

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
int cmp              (const void *a, const void *b);

#endif
