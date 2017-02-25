#include "sclib.h"

int sc_memory[reserve_memory];
int sc_reg_flags; // Регистр флагов
const int correct_commands[] = {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40,
						   0x41, 0x42, 0x43, 0x59};
const int commands_count = 13;
