#include <stdio.h>
/*统计文本空格数、tab数和行数*/

int main(int argc, char const *argv[]) {
  int c;
  double nblanks, ntabs, nnewlines;
  nblanks = ntabs = nnewlines = 0;

  while ((c = getchar()) != EOF) {
    switch (c) {
    case ' ':
      nblanks++;
      break;
    case '\t':
      ntabs++;
      break;
    case '\n':
      nnewlines++;
      break;
    }
  }

  printf("空格数\ttab数\t行数\n");
  printf("%.0f\t%.0f\t%.0f\n", nblanks, ntabs, nnewlines);

  return 0;
}
