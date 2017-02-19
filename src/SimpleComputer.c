#include "../core/includes/sclib.h"

int main(int argc, char const *argv[]) {
  int value;
  system("clear");
  sc_memoryInit();
  for (size_t i = 0; i < MEMSIZE; i++) {
    printf("+%3d ",sc_memory[i]);
  }
  printf("\n\n");
  sc_memorySet(5,999);
  sc_memoryGet(5,&value);
  for (size_t i = 0; i < MEMSIZE; i++) {
    printf("+%3d ",sc_memory[i]);
  }
  printf("\n\n");
  sc_memorySave("data.bin");
  sc_memoryLoad("data.bin");
  for (size_t i = 0; i < MEMSIZE; i++) {
    printf("+%3d ",sc_memory[i]);
  }
  printf("\n\n");
  return 0;
}
