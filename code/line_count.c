/*统计行数*/

#include <stdio.h>

int main(int argc, char const *argv[]) {
  long nl;
  int c;
  for (nl = 0; (c = getchar()) != EOF;) {
    if (c == '\n') {
      nl++;
    }
  }
  printf("行数：%ld\n", nl);
  return 0;
}
