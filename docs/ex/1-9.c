#include <stdio.h>
/*输出文本时将相邻的多个空格用一个空格代替输出。*/

#define IN 0
#define OUT 1 /*默认当前字符处于某个单词外*/

int main(int argc, char const *argv[]) {
  int c;
  int state = OUT;
  while ((c = getchar()) != EOF) {
    if (c != ' ') {
      putchar(c);
      state = IN;
    } else if (state == IN) {
      state = OUT;
      putchar(c); /*输出一次空格*/
    }
  }
  return 0;
}
