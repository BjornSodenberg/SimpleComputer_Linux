#include "sclib.h"

int sc_commandEncode (int command, int operand, int* value) {
  void *tcommand;

  tcommand = bsearch(&command, correct_commands, commands_count, sizeof(int), cmp);
  if (tcommand != NULL) {
    *value = (command << 7) | operand;
    return 0;
  }
  else
    return ERR_UCC;
}
