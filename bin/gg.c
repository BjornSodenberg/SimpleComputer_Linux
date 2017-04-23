#include "../core/includes/SC/sclib.h"
#include "../core/includes/BigChars/bigchrlib.h"
#include "../core/includes/Term/termlib.h"
#include "../core/includes/ReadKey/readkeylib.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// TODO: чтобы возможно было задавать значения ячейкам оперативной памяти, регистрам и обрабатывалось нажатие клавиш s, l.

int digit[19][2] = {{0x4242423C, 0x3C424242},  // 0
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
                    {0x00000000, 0x00000000},  // пустое знакоместо
                    {0x00181800, 0x00181800}}; // :

char instr[10], accum[10];
int status;
int isRunning = 1;
int ip;
// struct itimerval nval, oval; /* определение системного таймера */
void print_boxes();
void print_labels();
void print_mem(int *x,int *y);
void t_accumbox();
void t_counterbox();
void t_operationbox();
void t_flagbox();
void t_keybox();
void t_bcbox();
int change_mcell(int pos);
int Load();
int Save();
int scan_num(int *plus_flag, int *n);

int main(int argc, char const *argv[]) {
  int x = 0, y = 0, pos = 0;
  tl_clrscr();
  enum keys key;
  rk_termregime(0, 1, 1, 0,1);
  sc_memoryLoad("output");
  sc_regSet(flg_T,1);
  sc_memorySet(0, 0x4001);
  sc_memorySet(54, 0x999);
  // inst_counter = 54;
  sc_regSet(flg_T, 1);
  sc_regSet(flg_M, 1);
  rk_termregime(0, 0, 1, 0,1);
  print_boxes();
  print_labels();
  ip = 0;
    while (1) {
      pos = x*10+y;
      rk_termregime(0, 0, 1, 0,1);
      print_mem(&x, &y);

      t_accumbox();
      t_bcbox();
      t_counterbox();
      t_operationbox();
      t_flagbox();
      t_keybox();
      rk_readkey(&key);
      if(isRunning){
      switch(key){
        case l_key: Load(); break;
        case s_key: Save(); break;
        case up_key: x--; break;
        case down_key: x++; break;
        case left_key: y++; break;
        case right_key: y--; break;
        case f5_key: change_mcell(pos); break;
        case f6_key: break;
        default: break;
      }
    }
    }
  return 0;
}

int Load()
{
  rk_termregime(0, 1, 1, 1,1);
  char filename[256];

	printf("Enter save file name: ");
	fgets(filename, 256, stdin);
	filename[strlen(filename) - 1] = '\0';
	if (sc_memoryLoad(filename) == 0) {
		printf("File successfully loaded");
		return 0;
	}
	else {
		printf("Cannot load file: %s", filename);
		return -1;
	}
}
int Save()
{
  rk_termregime(0, 1, 1, 1,1);
  char filename[256];

	printf("Enter save file name: ");
	fgets(filename, 256, stdin);
	filename[strlen(filename) - 1] = '\0';
	if (sc_memorySave(filename) == 0) {;
		printf("File successfully saved");
		return 0;
	}
	else {
		printf("Cannot save file: %s", filename);
		return -1;
	}
}

void t_flagbox()
{
    tl_gotoXY(13, 79);
    write(STDOUT_FILENO, "_ _ _ _", 7 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_bcbox()
{
  if (status == 1)
    bc_printbigchar(digit[16], 16, 2, cmd_green, cmd_black);
  else
    bc_printbigchar(digit[17], 16, 2, cmd_green, cmd_black);
  for (int i = 1; i < 5; i++) {
    if (accum[i] == '0') bc_printbigchar(digit[0], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '1') bc_printbigchar(digit[1], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '2') bc_printbigchar(digit[2], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '3') bc_printbigchar(digit[3], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '4') bc_printbigchar(digit[4], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '5') bc_printbigchar(digit[5], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '6') bc_printbigchar(digit[6], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '7') bc_printbigchar(digit[7], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '8') bc_printbigchar(digit[8], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == '9') bc_printbigchar(digit[9], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == 'A' || instr[i] == 'a') bc_printbigchar(digit[10], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == 'B' || instr[i] == 'b') bc_printbigchar(digit[11], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == 'C' || instr[i] == 'c') bc_printbigchar(digit[12], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == 'D' || instr[i] == 'd') bc_printbigchar(digit[13], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == 'E' || instr[i] == 'e') bc_printbigchar(digit[14], 16, (i*10 + 2), cmd_green, cmd_black);
    if (accum[i] == 'F' || instr[i] == 'f') bc_printbigchar(digit[15], 16, (i*10 + 2), cmd_green, cmd_black);
  }

}

int change_mcell(int pos)
{
	int plus_flag, num;
	int command, operand, mem;
  rk_termregime(0, 1, 1, 1,1);
  // rk_termregime(0, 0, 1, 0,1);
  tl_gotoXY(33,0);
  write(1,"Enter num: ",12);
	if (scan_num(&plus_flag, &num) != 0) {
    tl_gotoXY(33,0);
		return -1;
	}

	if ((num >= 0) && (num < 0x8000)) {
		if (plus_flag) {
			if (((num >> 7) & 1) == 1) {
        tl_gotoXY(33,0);
				return -1;
			}
			command = (num >> 8) & 0x7F;
			operand = num & 0x7F;
			mem = (command << 7) | operand;
		}
		else
			mem = (1 << 14) | num;
		if ((pos >= 0) && (pos < 100))
			sc_memorySet(pos, mem);
	}
	else {
    tl_gotoXY(33,0);
		return -1;
	}
	return 0;
}

int scan_num(int *plus_flag, int *n)
{
	char buf[256];
	int pos = 0;
  rk_termregime(0, 1, 1, 1,1);

	fgets(buf, 256, stdin);
	if (buf[0] == '+') {
		pos = 1;
		*plus_flag = 1;
	}
	else
		*plus_flag = 0;
	if (sscanf(buf + pos, "%x", n) != 1)
		return -1;
	return 0;
}

void print_boxes()
{
  bc_box(1, 1, 14, 63);
  bc_box(1, 64, 4, 39);
  bc_box(5, 64, 3, 39);
  bc_box(8, 64, 4, 39);
  bc_box(12, 64, 3, 39);
  bc_box(15, 64, 10, 39);
  bc_box(15, 1, 10, 63);
}

void print_labels()
{
  tl_gotoXY(0, 28);
  write(1, " Memory ", 8 * sizeof(char));
  tl_gotoXY(1, 77);
  write(1, " accumulator ", 13 * sizeof(char));
  tl_gotoXY(5, 73);
  write(1, " instructionCounter ", 20 * sizeof(char));
  tl_gotoXY(8, 78);
  write(1, " Operation ", 11 * sizeof(char));
  tl_gotoXY(12, 79);
  write(1, " Flags ", 7 * sizeof(char));
  tl_gotoXY(15, 67);
  write(1, " Keys ", 7 * sizeof(char));

}

void print_mem(int *x,int *y)
{
  int mem, command;
  int opcode, operand;
  int k = 0;
  char buff[10];
  for (int i = 0; i < 10; i++) {

    for (int j = 0; j < 10; j++) {
      if (*x > 9)
          *x = 0;
      if (*x < 0)
          *x = 9;
      if (*y > 9)
          *y = 0;
      if (*y < 0)
          *y = 9;
      tl_gotoXY(2+i,3+j*6);
      mem = sc_memory[i*10+j] & 0x3FFF;
      command = (sc_memory[i*10+j] >> 14) & 1;
      opcode = (mem >> 7) & 0x7F;
      operand = mem & 0x7F;
			if (command == 0)
				sprintf(buff,"+%02X%02X", opcode, operand);
			else
				sprintf(buff," %02X%02X", opcode, operand);
      if(i == *x && j == *y){

        tl_setbgcolor(cmd_blue);
        tl_setfgcolor(cmd_black);
        if (command == 0) {
          sprintf(accum,"+%02X%02X", opcode, operand);
          status = 1;
        }
        else {
          sprintf(accum," %02X%02X", opcode, operand);
          status = 0;
        }
        write(1,buff,strlen(buff));
        *x == i;
        *y == j;
      }
      else{
        tl_setbgcolor(cmd_black);
        tl_setfgcolor(cmd_green);
        write(1,buff,strlen(buff));
        *x == i;
        *y == j;
      }
    }
    printf("\n\n");
  }

}

void t_accumbox()
{
    tl_gotoXY(2, 80);
    write(STDOUT_FILENO, accum, strlen(accum));
    tl_gotoXY(33, 0);
}

void t_counterbox(int pos)
{
    tl_gotoXY(6, 80);
    write(STDOUT_FILENO, "+9999", 5 * sizeof(char));
}

void t_operationbox()
{
    tl_gotoXY(9, 79);
    write(STDOUT_FILENO, "+00 : 00", 8 * sizeof(char));
    tl_gotoXY(33, 0);
}

void t_keybox()
{
    char *str[7] = {"l - load", "s - save", "r - run", "t - step", "i - reset", "F5 - accumulator", "F6 - instructionCounter"};
    for (int i = 0; i < 7; i++)
    {
        tl_gotoXY(16 + i, 66);
        write(STDOUT_FILENO, str[i], strlen(str[i]));
    }
    tl_gotoXY(33, 0);
}
