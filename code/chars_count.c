/*计算文本字符数*/

#include <stdio.h>

int main(int argc, char const *argv[]) {
  long nc;
  int c;
  for (nc = 0; (c = getchar()) != EOF; nc++)
    ;

  printf("字符数：%ld\n", nc);
  return 0;
}
