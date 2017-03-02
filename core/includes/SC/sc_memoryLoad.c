#include "sclib.h"

int sc_memoryLoad (char* filename) {
  FILE *save;
	int nreaden;
	int i;

	save = fopen(filename, "rb");
	if (save == NULL)
		return ERR_OFile;
	nreaden = fread(sc_memory, sizeof(*sc_memory) * 100, 1, save);
	fclose(save);
	if (nreaden != 1)
		return ERR_FSize;
	else
		return 0;
}
