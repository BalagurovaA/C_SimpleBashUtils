
#include <errno.h>  //обработка ошибок области определения, ошибочную последовательность байтов, при слишком большом результате
#include <getopt.h>
#include <limits.h>  //здесь определения характеристик общих типов переменных
#include <regex.h>   //поиск регулярных выражений
#include <stdbool.h>  //для подключения булевых знечений
#include <stdio.h>
#include <stdlib.h>  // для динамического управления памятью
#include <string.h>  // для функций strcopy, strcat, strlen
#define BUFF 9000

typedef struct {
  char pattern_e[BUFF];
  int e;  //   шаблон
  int v;  //   инверсия
  int i;  //   игнор регистра
  int c;  //   число совпадений
  int l;  //   имя файла, где есть шаблон
  int n;  //   номер строки и строку с шаблоном (if 2 файла + название)
  int h;  //   строки с шаблоном без названия файла
  int s;          //   рабоаeт с ложным файлом
  int f;          //   регулярные выражения из файла
  int file_flag;  // для количества фалйов
  int error;
  // char buff_for_fname[BUFFN][BUFFN]; //двумерный массив, через него читаю
  // файл, заношу туда строки
  int count_i_f;
  // char file_name[BUFF]; //массив, где у меня хранится file_name
  char line[BUFF];
} Flags;