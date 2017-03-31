#include "readkeylib.h"

int rk_termrestore()
{
  struct termios options;
  FILE *config_file;

  if ((config_file = fopen("../../../src/config.ini", "r")) == 0)
    return -1;

  fread(&options, sizeof(options), 1, config_file);

  return 0;
}
