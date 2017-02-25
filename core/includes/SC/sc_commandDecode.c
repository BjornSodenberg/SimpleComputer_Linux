#include "sclib.h"

int sc_commandDecode (int value, int* command, int* operand) {
  void *tcorrect_command;
  int attribute;
  int tmp_command, tmp_operand;

  attribute = (value >> 14) & 1;
  if (attribute == 0) {
    tmp_command = (value >> 7) & 0x7F;
    tmp_operand = value & 0x7F;
    tcorrect_command = bsearch(&tmp_command, correct_commands, commands_count,
                  sizeof(int), cmp);
    if (tcorrect_command != NULL) {
      *command = tmp_command;
      *operand = tmp_operand;
    }
    else
      return ERR_UCC;
  }
  else
    return ERR_AttrBit;
  return 0;
}
