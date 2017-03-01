#include "sclib.h"

int sc_memoryGet (int address, int* value) {
  if ((address >= 0) && (address < reserve_memory)) {
		*value = sc_memory[address];
		return 0;
	}
	else
		sc_regSet(flg_M,1);
}
