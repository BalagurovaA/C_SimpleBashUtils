#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int n_allnumbering;  //нумерует все выходные строки -n
  int e_dollar;  // также отображает символы конца строки как $ -e -v -E
  int b_notnumberingspace;  //нумерует только непустые строки -b
  int s_compression;  //сжимает несколько смежных пустых строк -s
  int tT_tabulation;  //также отображает табы как ^I -t -T
  int v;              //для флага v
} Flags;