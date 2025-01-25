#include "s21_cat.h"

Flags ReedFlags(int argc, char *argv[], int *indexx) {
  struct option longOOption[] = {{"number-nonblank", 0, NULL, 'b'},
                                 {"number", 0, NULL, 'n'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {NULL, 0, NULL, 0}};
  int currentFlag = getopt_long(argc, argv, "nevEbstT", longOOption, NULL);
  Flags flag = {0, 0, 0, 0, 0, 0};
  for (; currentFlag != -1;
       currentFlag = getopt_long(argc, argv, "nevEbstT", longOOption, NULL)) {
    switch (currentFlag) {
      case 'n':
        flag.n_allnumbering = 1;
        break;
      case 'e':
        flag.e_dollar = 1;
        flag.v = 1;
        break;
      case 'E':
        flag.e_dollar = 1;
        break;
      case 'b':
        flag.b_notnumberingspace = 1;
        break;
      case 's':
        flag.s_compression = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      case 't':
        flag.tT_tabulation = 1;
        flag.v = 1;
        break;
      case 'T':
        flag.tT_tabulation = 1;
        break;
      default:
        printf("usage: cat [-benstuv] [file ...]\n");
        break;
    }
  }
  *indexx = optind;
  return flag;
}
//функция для объединения файлов
void FLAG(char *file_name, Flags flag);

int main(int argc, char *argv[]) {
  int indexx;
  Flags flag = ReedFlags(argc, argv, &indexx);
  for (int i = indexx; i < argc; i++) {
    FLAG(argv[i], flag);
  }
}

void FLAG(char *file_name, Flags flag) {
  FILE *f = fopen(file_name, "r");
  if (f != NULL) {
    int c = fgetc(f);
    int prepre = '0';
    int pre = '\n';
    int numbB = 0;
    int numbN = 0;
    while (!feof(f)) {
      if ((flag.s_compression) && (c == '\n') && (prepre == '\n') &&
          (pre == '\n')) {
        prepre = pre;
        pre = c;
        c = fgetc(f);
        continue;
      }
      if ((flag.n_allnumbering) && (pre == '\n') &&
          (flag.b_notnumberingspace == 0)) {
        numbN++;
        printf("%6d\t", numbN);
      }
      if ((flag.b_notnumberingspace) && (pre == '\n') && (c != '\n')) {
        numbB++;
        printf("%6d\t", numbB);
      }
      if ((flag.e_dollar) && (c == '\n')) printf("$");
      if ((flag.tT_tabulation) && (c == '\t')) {
        printf("^");
        c += 64;
      }
      if (flag.v) {
        if (c > 127 && c < 160) printf("M-^");
        if ((c < 32 && c != '\n' && c != '\t') || c == 127) printf("^");
        if ((c < 32 || (c > 126 && c < 160)) && c != '\n' && c != '\t')
          c = c > 126 ? c - 128 + 64 : c + 64;
      }
      printf("%c", c);

      prepre = pre;
      pre = c;
      c = fgetc(f);
    }
    fclose(f);
  }
}
