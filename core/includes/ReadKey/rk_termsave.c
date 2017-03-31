#include "readkeylib.h"

int rk_termsave()
{
  struct termios options;
  FILE * config_file;
  config_file = fopen("../../../src/config.ini","w");
  fwrite( &options, sizeof(options), 1, config_file );
  fclose( config_file );
  return 0;
}
