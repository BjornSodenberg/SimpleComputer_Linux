#include "sclib.h"

int sc_memorySet (int address, int value) {
  if ((address >= 0) && (address < reserve_memory)) {
		sc_memory[address] = value;
		return 0;
	}
	else
		return ERR_WA;
}
