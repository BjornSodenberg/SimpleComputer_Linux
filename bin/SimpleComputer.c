#include "../core/includes/SC/sclib.h"
#include "../core/includes/BigChars/bigchrlib.h"
#include "../core/includes/Term/termlib.h"
#include "../core/includes/ReadKey/readkeylib.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

int digit[19][2] = {{0x4242423C, 0x3C424242},  // 0
                    {0x48506040, 0x40404040},  // 1
                    {0x2042423C, 0x7E020418},  // 2
                    {0x6064647C, 0x7C646030},  // 3
                    {0x66666666, 0x6060607E},  // 4
                    {0x7E02027E, 0x7E626060},  // 5
                    {0x3E02423C, 0x3C424242},  // 6
                    {0x2040407E, 0x10101010},  // 7
                    {0x3C42423C, 0x3C424242},  // 8
                    {0x7E42427E, 0xC183060},   // 9
                    {0x66663C18, 0x66667E7E},  // A
                    {0x3E66663E, 0x3E666666},  // B
                    {0x0202423C, 0x3C420202},  // C
                    {0x4444443E, 0x3E444444},  // D
                    {0x3E02027E, 0x7E020202},  // E
                    {0x1E02027E, 0x02020202},  // F
                    {0x7E181800, 0x0018187E},  // +
                    {0x00000000, 0x00000000},  // 
                    {0x00181800, 0x00181800}}; // :

char instr[10], accum[10] = "+0000", op[10];
int accumulator;
char instr_cntr[10];
int instructionCounter;
int status;
int ip = 0;
int x_i=0,y_i=0;
int x = 0, y = 0;
int t_opcode, t_operand, command;
int operand;
int opcode;
int pos;
void print_boxes();
void print_labels();
void print_mem(int *x,int *y);
void t_accumbox();
void t_counterbox();
void t_operationbox();
int t_flagbox();
void t_keybox();
void t_bcbox();
void t_input();
int change_mcell(int pos);
int Load();
int Save();
int scan_num(int *plus_flag, int *n);
int change_accum();
int change_op();
int reset();
int change_inst(int *x, int *y);

// SIGNAL
int flg_rr = 0;
int is_running = 1; 
int Run = 1;
void kr_run();
void kr_step();
int rise(int sig);
void signalhandler(int sig);
void signalusr(int sig);
struct itimerval nval, oval;
// ******

//***********
int ALU (int, int);
int CU (void);
int read_mcell(int pos);
int write_used, write_val;
//***********

int main(int argc, char const *argv[]) {
  pos = 0;
  tl_clrscr();
  enum keys key;
  rk_termregime(0, 1, 1, 0,1);
  sc_memoryLoad("output");
  sc_regInit();
  sc_memorySet(0, 0x4001);
  sc_memorySet(54, 0x999);
  sc_regSet(flg_T, Run);
  rk_termregime(0, 0, 1, 0,1);
  print_boxes();
  print_labels();
  ip = 0;
	signal(SIGALRM, signalhandler);
	signal(SIGUSR1, signalusr);
  if(Run ){
    while (1) {
      sc_regSet(flg_T, 1);
      pos = x*10+y;
      rk_termregime(0, 0, 1, 0,1);
      print_mem(&x, &y);
      t_accumbox();
      t_bcbox();
      t_counterbox();
      t_operationbox();
      t_keybox();
      t_flagbox();
      t_input();
      rk_readkey(&key);
      sc_regGet(flg_T, &is_running);
      switch(key){
        case l_key: {if (is_running == 1) Load(); break; }
        case s_key: {if (is_running == 1) Save(); break; }
        case up_key: { if (is_running == 1) x--; break; }
        case down_key: { if (is_running == 1) x++; break; }
        case left_key: { if (is_running == 1) y++; break; }
        case right_key: { if (is_running == 1) y--; break; }
        case i_key: { if (is_running == 1) reset(); break;}
        case f5_key:  { if (is_running == 1) change_accum(); break; }
        case f6_key:  { if (is_running == 1)change_inst(&x,&y);break; }
        case enter_key: { if (is_running == 1) change_mcell(pos); break; }
        case r_key: { if (is_running == 1)kr_run();  else { Run = 1; raise(SIGUSR1); } break; }
        case t_key: { if (is_running == 1)kr_step(); break; }
        default: break;
      }
    }
  }
  return 0;
}

int change_inst(int *x, int *y){
  char buff[5];
  int position = 0;
  float tmp = 0;
  int x_tmp = 0,y_tmp = 0;
  rk_termregime(0, 1, 1, 1,1);
  tl_gotoXY(27,2);
  write(1,"Enter position (0-99): ",24);
  fgets(buff, 4, stdin);
  sscanf(buff,"%d",&position);
  if(position >= 0 && position <= 99){
    x_tmp = position/10;
    y_tmp = position%10;

    *x = x_tmp;
    *y = y_tmp;
    sc_regSet(flg_M,0);
  }
  else
  {
    sc_regSet(flg_M,1);
  }
  return 0;
}


int reset()
{
  
  //Run = 1;
  x_i=0;
  y_i=0;
  x = 0;
  y = 0;
  accumulator = 0;
  sc_regSet(flg_P,0);
  sc_regSet(flg_T,1);
  sc_regSet(flg_O,0);
  sc_regSet(flg_E,0);
  sc_regSet(flg_M,0);
  sc_memoryInit();
}

int Load()
{
  rk_termregime(0, 1, 1, 1,1);
  char filename[256];
  tl_gotoXY(27,2);
	write(1,"Enter save file name: ",23);
	fgets(filename, 256, stdin);
	filename[strlen(filename) - 1] = '\0';
	if (sc_memoryLoad(filename) == 0) {
    tl_gotoXY(27,2);
		write(1,"File successfully loaded",40);
		return 0;
	}
	else {
    tl_gotoXY(27,2);
		write(1,"Cannot load file",20);
		return -1;
	}
}
int Save()
{
  rk_termregime(0, 1, 1, 1,1);
  char filename[256];
  tl_gotoXY(27,2);
	write(1,"Enter save file name: ",23);
	fgets(filename, 256, stdin);
	filename[strlen(filename) - 1] = '\0';
	if (sc_memorySave(filename) == 0) {
    tl_gotoXY(27,2);
		write(1,"File successfully saved",40);
		return 0;
	}
	else {
    tl_gotoXY(27,2);
		write(1,"Cannot save file",20);
		return -1;
	}
}

int change_accum(){
  int plus_flag, num;
	int command, operand;
  char buff[10];
  rk_termregime(0, 1, 1, 1,1);
  tl_gotoXY(27,2);
  write(1,"Enter num: ",12);
	if (scan_num(&plus_flag, &num) != 0) {
    tl_gotoXY(27,2);
		return -1;
	}

		if (plus_flag) {
			if (((num >> 7) & 1) == 1) {
        tl_gotoXY(27,2);
				return -1;
			}
			command = (num >> 8) & 0x7F;
			operand = num & 0x7F;
			accumulator = (command << 7) | operand;
		}

		else{
      accumulator = (1 << 14) | num;
    }

	return 0;
}

void t_input()
{
  tl_gotoXY(27, 2);
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 100; j++){
      write(1," ",2);
      tl_gotoXY(26+i, 2+j);
    }
  }
  tl_gotoXY(27,2);
}

int t_flagbox()
{
    tl_gotoXY(13, 79);
    int value;
    sc_regGet(flg_P,&value);
    if (value == 1) {
      write(1, "P ", 2);
    }
    else {
      write(1, "_ ", 2);
    }
    sc_regGet(flg_O,&value);
    if (value == 1) {
      write(1, "O ", 2);
    }
    else {
      write(1, "_ ", 2);
    }
    sc_regGet(flg_M,&value);
    if (value == 1) {
      write(1, "M ", 2);
    }
    else {
      write(1, "_ ", 2);
    }
    sc_regGet(flg_T,&value);
    if (value == 1) {
      write(1, "T ", 2);
    }
    else {
      write(1, "_ ", 2);
    }
    sc_regGet(flg_E,&value);
    if (value == 1) {
      write(1, "E ", 2);
    }
    else {
      write(1, "_ ", 2);
    }

    tl_gotoXY(33,0);
    return 0;
}

void t_bcbox()
{
  if (status == 1)
    bc_printbigchar(digit[16], 16, 2, cmd_green, cmd_black);
  else
    bc_printbigchar(digit[17], 16, 2, cmd_green, cmd_black);
  for (int i = 1; i < 5; i++) {
    if (instr[i] == '0') bc_printbigchar(digit[0], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '1') bc_printbigchar(digit[1], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '2') bc_printbigchar(digit[2], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '3') bc_printbigchar(digit[3], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '4') bc_printbigchar(digit[4], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '5') bc_printbigchar(digit[5], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '6') bc_printbigchar(digit[6], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '7') bc_printbigchar(digit[7], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '8') bc_printbigchar(digit[8], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == '9') bc_printbigchar(digit[9], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == 'A' || accum[i] == 'a') bc_printbigchar(digit[10], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == 'B' || accum[i] == 'b') bc_printbigchar(digit[11], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == 'C' || accum[i] == 'c') bc_printbigchar(digit[12], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == 'D' || accum[i] == 'd') bc_printbigchar(digit[13], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == 'E' || accum[i] == 'e') bc_printbigchar(digit[14], 16, (i*10 + 2), cmd_green, cmd_black);
    if (instr[i] == 'F' || accum[i] == 'f') bc_printbigchar(digit[15], 16, (i*10 + 2), cmd_green, cmd_black);
  }

}

int change_mcell(int pos)
{
	int plus_flag, num;
	int command, operand, mem;
  char buff[10];
  rk_termregime(0, 1, 1, 1,1);
  tl_gotoXY(27,2);
  write(1,"Enter num: ",12);
	if (scan_num(&plus_flag, &num) != 0) {
    tl_gotoXY(27,2);
		return -1;
	}

		if (plus_flag) {
			if (((num >> 7) & 1) == 1) {
        tl_gotoXY(27,2);
				return -1;
			}
			command = (num >> 8) & 0x7F;
			operand = num & 0x7F;
			mem = (command << 7) | operand;
		}

		else{
      mem = (1 << 14) | num;
    }

		if ((pos >= 0) && (pos < 100))
			sc_memorySet(pos, mem);
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
	if (sscanf(buf + pos, "%X", n) != 1)
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
  bc_box(25, 1, 10, 102);
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
  int mem;
  int k = 0;
  int pos;
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
      pos = *x*10+*y;
      ip= pos;
      sprintf(instr_cntr,"%d",ip);
      mem = sc_memory[i*10+j] & 0x3FFF;
      command = (sc_memory[i*10+j] >> 14) & 1;
      opcode = (mem >> 7) & 0x7F;
      operand = mem & 0x7F;
			if (command == 0) {
				sprintf(buff,"+%02X%02X", opcode, operand);
      }
			else {
				sprintf(buff," %02X%02X", opcode, operand);
      }
      if(i == *x && j == *y){

        tl_setbgcolor(cmd_red);
        tl_setfgcolor(cmd_black);
        if (command == 0) {
          sprintf(instr,"+%02X%02X", opcode, operand);
          sprintf(op,"+%02X:%02X", opcode, operand);
          status = 1;
          sc_regSet(flg_E,0);

        }
        else {
          sprintf(instr," %02X%02X", opcode, operand);
          sprintf(op," %02X:%02X", opcode, operand);
          status = 0;
          sc_regSet(flg_E,1);
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
    int mem;
    int k = 0;
    int pos;

    if (accumulator == 0){
      sprintf(accum,"+0000");
    }
    else {
      mem = accumulator & 0x3FFF;
      command = (accumulator >> 14) & 1;
      if (command == 0) {
          sprintf(accum,"+%X", mem);
      }
      else {
          sprintf(accum," %X", mem);
      }
    }
    tl_gotoXY(2, 80);
    write(STDOUT_FILENO, accum, strlen(accum));
    tl_gotoXY(27, 2);
}

void t_counterbox()
{
    tl_gotoXY(6, 80);
    write(1,"      ",7);
    tl_gotoXY(6, 80);
    write(STDOUT_FILENO, instr_cntr, strlen(instr));
}

void t_operationbox()
{
    tl_gotoXY(9, 79);
    write(STDOUT_FILENO, op, 8 * sizeof(char));
    tl_gotoXY(27, 2);
}

void t_keybox()
{
    char *str[7] = {"l - load", "s - save", "r - run", "t - step", "i - reset", "F5 - accumulator", "F6 - instructionCounter"};
    for (int i = 0; i < 7; i++)
    {
        tl_gotoXY(16 + i, 66);
        write(STDOUT_FILENO, str[i], strlen(str[i]));
    }
    tl_gotoXY(27, 2);
}

void kr_run()
{
  enum keys key;
  if(Run){;
    sc_regSet(flg_T,0);
    Run = 0;
    signal(SIGALRM, signalhandler);
    nval.it_interval.tv_sec = 1;
    nval.it_interval.tv_usec = 0;
    nval.it_value.tv_sec = 1;
    nval.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &nval, &oval);

  }
}

void kr_step()
{
    if (ip + 1 <= reserve_memory) {
        ip++;
        x = ip / 10;
        y = ip % 10;
    }
}

void signalhandler(int sig)
{
  
  //rk_termregime(1, 1, 1, 0,1);
  if(Run == 0 && sig == SIGALRM ){
    if (ip + 1 <= reserve_memory) {
      sc_regSet(flg_T,0);
      x = ip / 10;
      y = ip % 10;
      print_mem(&x, &y);
      t_accumbox();
      t_bcbox();
      t_counterbox();
      t_operationbox();
      t_keybox();
      t_flagbox();
      CU();
      ip++;
    }
  }
}
void signalusr(int sig)
{
//  rk_termregime(1, 1, 1, 0,1);
	alarm(0);
	//reset();
}

int read_mcell(int pos)
{
	int plus_flag, num;
	int command_d, operand_d, mem;

	print_mem(&x, &y);
    t_accumbox();
    t_bcbox();
    t_counterbox();
    t_operationbox();
    t_keybox();
    t_flagbox();
    t_input();
	printf("READ: ");
	if (scan_num(&plus_flag, &num) != 0) {
		printf("Not a number!");
		return -1;
	}
	if ((num >= 0) && (num < 0x8000)) {
		if (plus_flag) {
			if (((num >> 7) & 1) == 1) {
				printf("Wrong instruction allign");
				return -1;
			}
			command_d = (num >> 8) & 0x7F;
			operand_d = num & 0x7F;
			mem = (command_d << 7) | operand_d;
		}
		else 
			mem = (1 << 14) | num;
		if ((pos >= 0) && (pos < 100))
			sc_memorySet(pos, mem);
	}
	else {
		printf("Memory cell is 15 bit wide");
		return -1;
	}
	return 0;
}

/*
 Реализует алгоритм работы арифметико-
логического устройства. Если при выполнении функции возникла ошибка, которая не
позволяет дальше выполнять программу, то функция возвращает -1, иначе 0;
 */
int ALU (int comm, int oper)
{
    int tmp;
    switch(comm)
    {
        case 0x30:
        {
            accumulator += sc_memory[oper];
            break;
        }
        case 0x31:
        {
            if (((sc_memory[oper] >> 14) & 1) == 1)
				tmp = sc_memory[oper] | (~0x7FFF);
			else
				tmp = sc_memory[oper];
			accumulator -= tmp;
			if ((accumulator > ((int)(~0x7FFF))) && (accumulator <= 0x7FFF)) {
				accumulator &= 0x7FFF;
			}
            break;
        }
        case 0x32:
        {
            if (sc_memory[oper] != 0)
				accumulator /= sc_memory[oper];
			else {
				sc_regSet(flg_P, 1);
				return -1;
			}
            break;
        }
        case 0x33:
        {
            accumulator *= sc_memory[oper];
            break;
        }
    if ((accumulator & 1) == 0)
		sc_regSet(flg_O, 0);
	else
		sc_regSet(flg_O, 1);
	if ((accumulator > 0x7FFF) || (accumulator < 0)) {
		accumulator &= 0x7FFF;
		sc_regSet(flg_M, 1);
	}
	else
		sc_regSet(flg_P, 0);
	sc_regSet(flg_O, accumulator & 1);
    }
    return 0;
}
/*
 обеспечивает работу устройства управления.
 */
int CU (void)
{
    int command_d, operand_d;
    int flag, read_suc;
    char buff[2];
    if (ip >= reserve_memory)
    {
        sc_regSet(flg_M,1);
        sc_regSet(flg_T,1);
        return -1;
    }
//    if(sc_commandDecode(sc_memory[ip],&command_d, &operand_d) != 0)
//    {
//        sc_regSet(flg_E,1);
//        sc_regSet(flg_T,1);
//        
//        return -1;
//    }
    int mem_d;
    mem_d = sc_memory[ip] & 0x3FFF;
    command_d = (mem_d >> 7) & 0x7F;
    operand_d = mem_d & 0x7F;
    if(operand_d < 0 && operand_d >= reserve_memory)
    {
        sc_regSet(flg_E,1);
        sc_regSet(flg_T,1);
        return -1;
    }
    if(command_d >= 0x30 && command_d <= 0x33)
    {
        if(ALU(command_d,operand_d) != 0)
            sc_regSet(flg_T,1);
    }
    else
    {
        sprintf(buff,"%x",operand_d);
        operand_d = atoi(buff);
        write(1,buff,2);
        switch(command_d)
        {
            case 0x10://READ
            {
                do{
                    read_suc = read_mcell(operand_d);  
                }while(read_suc != 0);
                break;
            }
                
            case 0x11://WRITE
            {
                write_used = 1;
                write_val = sc_memory[operand_d];
                break;
            }
            case 0x20://LOAD
            {
                accumulator = sc_memory[operand_d];
                break;
            }
            case 0x21://STORE
            {
                sc_memory[operand_d] = accumulator;
                break;
            }
            case 0x40://JUMP
            {
                ip = operand_d-1;
                break;
            }
            case 0x41://JNEG
            {
                if(((accumulator >> 14) & 1)==1)
                    ip = operand_d - 1;
                break;
            }
            case 0x42://JZ
            {
                if(accumulator == 0)
                    ip = operand_d - 1;
                break;
            }
            case 0x43://HALT
            {
                sc_regSet(flg_T,1);
                break;
            }
            case 0x59://JNP
            {
                sc_regGet(flg_P,&flag);
                if(flag == 1)
                    ip = operand - 1;
                break;
            }      
        }
    }
    return 0;
}


/*
 Обработку команд осуществляет устройство управления. Функция CU вызывается либо обра-
ботчиком сигнала от системного таймера, если не установлен флаг «игнорирование тактовых им-
пульсов», либо при нажатии на клавишу t. Алгоритм работы функции следующий:
    1. из оперативной памяти считывается ячейка, адрес которой храниться в регистре instruc-
tionCounter;
    2. полученное значение декодируется как команда;
    3. если декодирование невозможно, то устанавливаются флаги «указана неверная команда» и
«игнорирование тактовых импульсов» (системный таймер можно отключить) и работа
функции прекращается.
    4. Если получена арифметическая или логическая операция, то вызывается функция ALU,
иначе команда выполняется самим устройством управления.
    5. Определяется, какая команда должна быть выполнена следующей и адрес еѐ ячейки памя-
ти заносится в регистр instructionCounter.
    6. Работа функции завершается.
 */