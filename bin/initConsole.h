#ifndef INITCONSOLE_H
#define INITCONSOLE_H

#include "../core/includes/SC/sclib.h"
#include "../core/includes/BigChars/bigchrlib.h"
#include "../core/includes/Term/termlib.h"
#include "../core/includes/ReadKey/readkeylib.h"

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

void t_memorybox();
void t_accumbox();
void t_counterbox();
void t_operationbox();
void t_flagbox();
void t_keybox();
void t_bcbox();
void t_init();


#endif
