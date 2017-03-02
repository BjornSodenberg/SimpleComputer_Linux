#include "sclib.h"

int sc_memoryInit()
{
	//memset(sc_memory, 0, sizeof(*sc_memory));
	for (size_t i = 0; i < reserve_memory; i++) {
		sc_memory[i] = 0;
	}
	return 0;
}
