#include "sclib.h"

int sc_commandEncode (int command, int operand, int* value) {
  int *tcommand;

  tcommand = (int*)bsearch(&command, correct_commands, commands_count, sizeof(int), cmp);
  if (tcommand != NULL) {
    *value = (command << 7) | operand;
    return 0;
  }
  else
    sc_regSet(flg_E,1);
}
