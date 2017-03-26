#include "termlib.h"

int tl_setfgcolor(enum colors color){
  char fg[30];
  sprintf(fg, "\e[38;5;%dm", color);
  ssize_t len = strlen(fg) * sizeof(char);
  if (write(1, fg, strlen(fg)) < len)
  {
      return -1;
  }
  return 0;
}
