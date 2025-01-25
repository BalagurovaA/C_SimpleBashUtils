#include "s21_grep.h"

void reed_flags(int argc, char *argv[], Flags *flag) {
  int currentFlag = getopt_long(
      argc, argv, "e:vcixlnhsf:o", NULL,
      0);  // NULL-длинных опций нет  0- не надо передавать указатель на
           // переменную, которая будет хранить индекс следующего аргумента
           // командной строки, после обработки длинных опций
  for (; currentFlag != -1;
       currentFlag = getopt_long(argc, argv, "e:vcixlnhsf:o", NULL, 0)) {
    switch (currentFlag) {
      case 'e':
        flag->e = 1;
        strcat(flag->pattern_e, optarg);  // strcat(куда, откуда);
        strcat(flag->pattern_e, "|");
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      default:
        flag->error = 1;
        break;
    }
  }
  if (!flag->e && !flag->f) {
    if (argc > optind) {
      strcat(flag->pattern_e, argv[optind]);
    }
    optind++;
  }
  if (flag->e || flag->f) {
    flag->pattern_e[strlen(flag->pattern_e) - 1] =
        '\0';  //последнее записанное значение
  }
  if ((argc - optind) > 1) flag->file_flag = 1;
}

// объявление функций
void output(char *argv[], Flags *flag, int argc, int index_f);

int main(int argc, char *argv[]) {
  // char new_mass_f[BUFF] = {'\0'};
  Flags flag = {0};
  reed_flags(argc, argv, &flag);
  int index_f = optind;  //чтобы optind постоянно не увеличивался
  while (optind < argc) {  // чтобы обрабатывать новый файл
    output(argv, &flag, argc, index_f);
    optind++;
  }
  return 0;
}

void output(char *argv[], Flags *flag, int argc, int index_f) {
  int n = 0;    //счетчик строк для флага н
  regex_t reg;  //здесь инфа о скомпилированном регулярном выражении
  regmatch_t start;  // здесь инфа о совпадениях рег выражения и строки
  int c_count = 0;   //счетчик совпадений

  flag->file_flag =
      (index_f + 1 < argc);  //условие на то, что у меня не один файл
  int flag_i = REG_EXTENDED;
  if (flag->i) {
    flag_i = REG_EXTENDED | REG_ICASE;  // REG_EXTENDED имеет более широкий
                                        // синтаксис регулярных выражений
  }
  regcomp(&reg, flag->pattern_e, flag_i);  // компилирую регулярные выражения
  FILE *file = fopen(argv[optind], "rb");
  if (file) {
    while (fgets(flag->line, BUFF, file) != NULL) {
      n++;
      int match = regexec(&reg, flag->line, 1, &start,
                          0);  // количество совпадений но функция regexec
                               // возвращает либо 1 либо 0

      if (flag->v) match = !match;  // 1 нет совпадений, 0 есть
      if (!match) c_count++;
      if (!match && flag->file_flag && !flag->h && !flag->c && !flag->l) {
        printf("%s:", argv[optind]);
      }
      if (!match && !flag->c && !flag->l && flag->n) {
        printf("%d:", n);
      }
      if (!match && !flag->c && !flag->l) {
        printf("%s", flag->line);
        if (flag->line[strlen(flag->line) - 1] != '\n') printf("\n");
      }
    }
    if (flag->c) {
      if (flag->file_flag && !flag->h) printf("%s:", argv[optind]);
      if (flag->l && c_count > 0) c_count = 1;
      printf("%d\n", c_count);
    }
    if (flag->l && c_count > 0) {
      printf("%s\n", argv[optind]);
    }
    fclose(file);
  }
  if (!file)
    fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
  regfree(&reg);
}