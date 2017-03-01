#include "termlib.h"

int tl_setfgcolor(enum colors color){
  switch (color) {
    case cmd_black:      printf("\E[30m"); break;
    case cmd_blue:       printf("\E[31m"); break;
    case cmd_green:      printf("\E[32m"); break;
    case cmd_cyan:       printf("\E[33m"); break;
    case cmd_red:        printf("\E[34m"); break;
    case cmd_magenta:    printf("\E[35m"); break;
    case cmd_brown:      printf("\E[36m"); break;
    case cmd_light_blue: printf("\E[39m"); break;
    case cmd_default:    printf("\E[30m"); break;
    default:                               return -1;
  }
  return 0;
}
