#include "../../core/includes/SC/sclib.h"

int main(int argc, char const *argv[]) {
  int mem1, mem2;
	int bit1, bit2;
	int comm1, comm2;
	int command, operand;
	int ret;

	sc_memoryInit();
	sc_memorySet(3, 0x5);
	sc_memoryGet(1, &mem1);
	sc_memoryGet(3, &mem2);
	printf("0?%X :: 5?%X\n", mem1, mem2);
	sc_memorySave("memory");
	/* Меняем ячейку памяти, загружаем память в неизмененном состоянии */
	sc_memorySet(3, 0x10);
	sc_memoryLoad("memory");
	sc_memoryGet(3, &mem1);
	printf("5?%X\n", mem1);
	/* Проверка функций работы с регистром флагов */
	sc_regInit();
	sc_regSet(flg_M, 1);
	sc_regSet(flg_E, 1);
	printf("Flag register is %X\n", sc_reg_flags);
	sc_regGet(flg_M, &bit1);
	sc_regSet(flg_E, 0);
	sc_regGet(flg_E, &bit2);
	printf("1?%d 0?%d\n", bit1, bit2);
	/* Кодирование/декодирование комманд */
	sc_commandEncode(0x21, 4, &comm1);
  sc_regGet(flg_E,&ret);
	printf("Encoded command is %X Return value: %d\n", comm1, ret);
  sc_regSet(flg_E,0);
	sc_commandEncode(0x4, 4, &comm2);
  sc_regGet(flg_E,&ret);
	printf("Encoded command is %X Return value: %d\n", comm2, ret);
  sc_regSet(flg_E,0);
	sc_commandDecode(0x1084, &command, &operand);
  sc_regGet(flg_E,&ret);
	printf("Command; %d Operand: %d Return value: %d\n", command, operand, ret);
  sc_regSet(flg_E,0);
	sc_commandDecode(0xB84, &command, &operand);
  sc_regGet(flg_E,&ret);
	printf("Command; %d Operand: %d Return value: %d\n", command, operand, ret);
	return 0;
}
