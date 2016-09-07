/*将输入内容输出，每行只输出一个单词。*/
#include <stdio.h>

#define IN 1  /*在单词内*/
#define OUT 0 /*在单词外*/

int main(int argc, char const *argv[]) {
  int c;
  int state = OUT;
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      putchar('\n');
      putchar(c);
    } else {
      putchar(c);
    }
  }
  putchar('\n');
  return 0;
}
