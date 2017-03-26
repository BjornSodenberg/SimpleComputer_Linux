#include "termlib.h"

int tl_setbgcolor(enum colors color){
  char bg[30];
  sprintf(bg, "\e[48;5;%dm", color);
  ssize_t len = strlen(bg) * sizeof(char);
  if (write(1, bg, strlen(bg)) < len)
  {
      return -1;
  }
  return 0;
}
