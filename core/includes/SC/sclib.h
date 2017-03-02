#ifndef SCLIB_H
#define SCLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define reserve_memory 100

#define flg_P 1
#define flg_O 2
#define flg_M 3
#define flg_T 4
#define flg_E 5

#define ERR_OFile -1
#define ERR_FSize -2
#define ERR_AttrBit -3
#define ERR_WF -4
#define ERR_UCC -5

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
int sc_regSet        (int registr, int value);
int sc_regGet        (int registr, int* value);
int sc_commandEncode (int command, int operand, int* value);
int sc_commandDecode (int value, int* command, int* operand);
int cmp              (const void *a, const void *b);

#endif
