#include <stdio.h>
/*输出文本时将相邻的多个空格用一个空格代替输出。*/

#define IN 0
#define OUT 1 /*默认当前字符处于某个单词外*/

int main1(int argc, char const *argv[]) {
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

/*跟踪上一个字符
当前字符是空格：
        如果上一个字符是空格，不输出任何内容
        如果上一个字符不是空格，输出
当前字符不是空格：
        输出字符
*/
int mai2(int argc, char const *argv[]) {
  int c;
  int prev = EOF; /*上一个字符*/
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      if (prev != ' ') {
        putchar(c);
      }
    } else {
      putchar(c);
    }

    prev = c;
  }
  return 0;
}

/*
当前字符为空字符时，输出，并“吃掉"紧随的所有空字符
*/
int main(int argc, char const *argv[]) {
  int c;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      putchar(c);
      while ((c = getchar()) != EOF && c == ' ')
        ;
    }
    if (c == EOF) {
      break;
    }
    putchar(c);
  }

  return 0;
}
