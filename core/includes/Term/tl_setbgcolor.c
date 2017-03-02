#include "termlib.h"

int tl_setbgcolor(enum colors color){
  switch (color) {
    case cmd_black:      printf("\E[40m"); break;
    case cmd_red:        printf("\E[41m"); break;
    case cmd_green:      printf("\E[42m"); break;
    case cmd_brown:      printf("\E[43m"); break;
    case cmd_blue:       printf("\E[44m"); break;
    case cmd_magenta:    printf("\E[45m"); break;
    case cmd_cyan:       printf("\E[46m"); break;
    case cmd_light_blue: printf("\E[47m"); break;
    case cmd_default:    printf("\E[49m"); break;
    default:                               return -1;
  }
  return 0;
}
