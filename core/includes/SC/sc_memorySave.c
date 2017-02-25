#include "sclib.h"

int sc_memorySave (char* filename) {
  FILE *save;
	int nwritten;

	save = fopen(filename, "wb");
	if (save == NULL)
		return ERR_OFile;
	nwritten = fwrite(sc_memory, sizeof(*sc_memory) * 100, 1, save);
	fclose(save);
	if (nwritten != 1)
		return ERR_FSize;
	else
		return 0;
}
