#include "../../core/includes/Term/termlib.h"

int main() {
  int return_value;
  int rows,cols;
  int x,y;
  enum colors cmd_blueti;
  enum colors cmd_ruby;
  tl_clrscr();
  // ***********getscrennsize************

    return_value = tl_getscreensize(&rows,&cols);
    printf("rows:%d cols: %d return_value getscrennsize: %d\n",
        rows,cols,return_value);
  // ************************************

  // **************gotoXY****************
    x = 5;
    y = 10;
    return_value = tl_gotoXY(x,y);
    printf("return_value gotoXY: %d\n",return_value);
  // ************************************
  // **************gotoXY****************
    x = -1;
    y = 100;
    return_value = tl_gotoXY(x,y);
    printf("return_value gotoXY: %d \n",return_value);
  // ************************************

  // **************Setbgcolor************
    return_value = tl_setbgcolor(cmd_red);

    printf("return_value Setbgcolor: %d\n",return_value);
    tl_setbgcolor(cmd_black);
  // ************************************
  // **************Setgbcolor************
    return_value = tl_setbgcolor(cmd_blueti);
    printf("return_value Setbgcolor: %d\n",return_value);
    tl_setbgcolor(cmd_black);
  // ************************************

  // **************Setfgcolor************
    return_value = tl_setfgcolor(cmd_blue);
    printf("return_value Setgbcolor: %d\n",return_value);
    tl_setfgcolor(cmd_default);
  // ************************************
  // **************Setfgcolor************
    return_value = tl_setfgcolor(cmd_ruby);
    printf("return_value Setgbcolor: %d\n",return_value);
    tl_setfgcolor(cmd_default);
  // ************************************

  return 0;
}
