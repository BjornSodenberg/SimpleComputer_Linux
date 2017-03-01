#include "sclib.h"

int sc_commandDecode (int value, int* command, int* operand) {
  int* tcorrect_command;
  int attribute;
  int tmp_command, tmp_operand;

  attribute = (value >> 14) & 1;
  if (attribute == 0) {
    tmp_command = (value >> 7);
    tmp_operand = value;
    tcorrect_command = (int*)bsearch(&tmp_command, correct_commands, commands_count,
                  sizeof(int), cmp);
    if (tcorrect_command != NULL) {
      *command = tmp_command;
      *operand = tmp_operand;
    }
    else
      sc_regSet(flg_E,1);
  }
  else
    return ERR_AttrBit;
}
