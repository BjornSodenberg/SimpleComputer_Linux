#include "initConsole.h"

void t_memorybox()
{
    int value,k = 0;
    tl_setbgcolor(cmd_default);
    tl_setfgcolor(cmd_magenta);
    bc_box(1, 1, 14, 63);
    tl_gotoXY(0, 28);
    write(1, " Memory ", 8 * sizeof(char));
    for (int j = 3; j < 63; j += 6)
    {
        for (int i = 2; i < 14; ++i)
        {
            tl_gotoXY(i, j);
            sc_memoryGet (k, &value);
            write(1, "+", sizeof(char));
            write(1, value , 5 * sizeof(char));
            k++;
        }
    }
    tl_gotoXY(33, 0);
}

void t_accumbox()
{
    tl_setbgcolor(cmd_default);
    tl_setfgcolor(cmd_magenta);
    bc_box(1, 64, 4, 39);
    tl_gotoXY(1, 77);
    write(1, " accumulator ", 13 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    tl_gotoXY(2, 80);
    write(1, "+9999", 5 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_counterbox()
{
    tl_setbgcolor(cmd_default);
    tl_setfgcolor(cmd_magenta);
    bc_box(5, 64, 3, 39);
    tl_gotoXY(5, 73);
    write(1, " instructionCounter ", 20 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    tl_gotoXY(6, 80);
    write(1, "+9999", 5 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_operationbox()
{
    tl_setbgcolor(cmd_default);
    tl_setfgcolor(cmd_magenta);
    bc_box(8, 64, 4, 39);
    tl_gotoXY(8, 78);
    write(1, " Operation ", 11 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    tl_gotoXY(9, 79);
    write(1, "+00 : 00", 8 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_flagbox()
{
    tl_setbgcolor(cmd_default);
    tl_setfgcolor(cmd_magenta);
    bc_box(12, 64, 3, 39);
    tl_gotoXY(12, 79);
    write(1, " Flags ", 7 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    tl_gotoXY(13, 79);
    write(1, "O E V M", 7 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_keybox()
{
    tl_setbgcolor(cmd_default);
    tl_setfgcolor(cmd_magenta);
    bc_box(15, 64, 10, 39);
    tl_gotoXY(15, 67);
    write(1, " Keys ", 7 * sizeof(char));
    tl_setfgcolor(cmd_magenta);
    char *str[7] = {"l - load", "s - save", "r - run", "t - step", "i - reset", "F5 - accumulator", "F6 - instructionCounter"};
    for (int i = 0; i < 7; i++)
    {
        tl_gotoXY(16 + i, 66);
        write(1, str[i], strlen(str[i]));
    }
    tl_gotoXY(33, 0);
}

void t_bcbox()
{
    tl_setbgcolor(cmd_default);
    tl_setfgcolor(cmd_magenta);
    bc_box(15, 1, 10, 63);
    bc_printbigchar(digit[16], 16, 2, cmd_magenta, cmd_default);

    bc_printbigchar(digit[9], 16, 12, cmd_magenta, cmd_default);
    bc_printbigchar(digit[9], 16, 22, cmd_magenta, cmd_default);
    bc_printbigchar(digit[9], 16, 32, cmd_magenta, cmd_default);
    bc_printbigchar(digit[9], 16, 42, cmd_magenta, cmd_default);
    tl_gotoXY(33, 0);
}

void t_init()
{
    sc_memoryInit();
    t_memorybox();
    t_accumbox();
    t_counterbox();
    t_operationbox();
    t_flagbox();
    t_keybox();
    t_bcbox();
}
