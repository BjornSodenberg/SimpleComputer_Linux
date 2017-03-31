#include "../../core/includes/BigChars/bigchrlib.h"
#include "../../core/includes/Term/termlib.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int digit[18][2] = {{0x4242423C, 0x3C424242},  // 0
                    {0x48506040, 0x40404040},  // 1
                    {0x2042423C, 0x7E020418},  // 2
                    {0x3840423C, 0x3C424040},  // 3
                    {0x7E424478, 0x40404040},  // 4
                    {0x3E02027E, 0x3C424040},  // 5
                    {0x3E02423C, 0x3C424242},  // 6
                    {0x2040407E, 0x10101010},  // 7
                    {0x3C42423C, 0x3C424242},  // 8
                    {0x7C42423C, 0x3C424040},  // 9
                    {0x66663C18, 0x66667E7E},  // A
                    {0x3E66663E, 0x3E666666},  // B
                    {0x0202423C, 0x3C420202},  // C
                    {0x4444443E, 0x3E444444},  // D
                    {0x3E02027E, 0x7E020202},  // E
                    {0x1E02027E, 0x02020202},  // F
                    {0x7E181800, 0x0018187E},  // +
                    {0x00181800, 0x00181800}}; // :

void t_memorybox()
{
    tl_setbgcolor(cmd_black);
    tl_setfgcolor(cmd_magenta);
    bc_box(1, 1, 14, 63);
    tl_gotoXY(0, 28);
    write(STDOUT_FILENO, " Memory ", 8 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    for (int j = 3; j < 63; j += 6)
    {
        for (int i = 2; i < 14; ++i)
        {
            tl_gotoXY(i, j);
            write(STDOUT_FILENO, "+9999 ", 6 * sizeof(char));
        }
    }
    tl_gotoXY(33, 0);
}

void t_accumbox()
{
    tl_setbgcolor(cmd_black);
    tl_setfgcolor(cmd_magenta);
    bc_box(1, 64, 4, 39);
    tl_gotoXY(1, 77);
    write(STDOUT_FILENO, " accumulator ", 13 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    tl_gotoXY(2, 80);
    write(STDOUT_FILENO, "+9999", 5 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_counterbox()
{
    tl_setbgcolor(cmd_black);
    tl_setfgcolor(cmd_magenta);
    bc_box(5, 64, 3, 39);
    tl_gotoXY(5, 73);
    write(STDOUT_FILENO, " instructionCounter ", 20 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    tl_gotoXY(6, 80);
    write(STDOUT_FILENO, "+9999", 5 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_operationbox()
{
    tl_setbgcolor(cmd_black);
    tl_setfgcolor(cmd_magenta);
    bc_box(8, 64, 4, 39);
    tl_gotoXY(8, 78);
    write(STDOUT_FILENO, " Operation ", 11 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    tl_gotoXY(9, 79);
    write(STDOUT_FILENO, "+00 : 00", 8 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_flagbox()
{
    tl_setbgcolor(cmd_black);
    tl_setfgcolor(cmd_magenta);
    bc_box(12, 64, 3, 39);
    tl_gotoXY(12, 79);
    write(STDOUT_FILENO, " Flags ", 7 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    tl_gotoXY(13, 79);
    write(STDOUT_FILENO, "O E V M", 7 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_keybox()
{
    tl_setbgcolor(cmd_black);
    tl_setfgcolor(cmd_magenta);
    bc_box(15, 64, 10, 39);
    tl_gotoXY(15, 67);
    write(STDOUT_FILENO, " Keys ", 7 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    char *str[7] = {"l - load", "s - save", "r - run", "t - step", "i - reset", "F5 - accumulator", "F6 - instructionCounter"};
    for (int i = 0; i < 7; i++)
    {
        tl_gotoXY(16 + i, 66);
        write(STDOUT_FILENO, str[i], strlen(str[i]));
    }
    tl_gotoXY(33, 0);
}

void t_bcbox()
{
    tl_setbgcolor(cmd_black);
    tl_setfgcolor(cmd_magenta);
    bc_box(15, 1, 10, 63);
    bc_printbigchar(digit[16], 16, 2, cmd_magenta, cmd_black);

    bc_printbigchar(digit[9], 16, 12, cmd_magenta, cmd_black);
    bc_printbigchar(digit[9], 16, 22, cmd_magenta, cmd_black);
    bc_printbigchar(digit[9], 16, 32, cmd_magenta, cmd_black);
    bc_printbigchar(digit[9], 16, 42, cmd_magenta, cmd_black);
    tl_gotoXY(33, 0);
}

void t_init()
{
    t_memorybox();
    t_accumbox();
    t_counterbox();
    t_operationbox();
    t_flagbox();
    t_keybox();
    t_bcbox();
}

int main(int argc, char const *argv[]) {
  tl_clrscr();
  t_init();

  tl_gotoXY(30, 0);

  int fd;
  fd = open("file",O_WRONLY);
  bc_bigcharwrite(fd,digit[9],5);
  close(fd);

  int tcount = 0;
  fd = open("file",O_RDONLY);
  bc_bigcharread(fd,digit[9],1,&tcount);
  close(fd);

  tl_gotoXY(33, 0);

  return 0;
}
