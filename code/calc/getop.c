// getop实现
#include "calc.h"
#include <ctype.h>
#include <stdio.h>

int getop(char s[]) {
  int c, i;
  // 跳过空字符
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  //如果是操作字符
  if (!isdigit(c) && c != '.') {
    s[1] = '\0';
    return c;
  }
  //如果是数字字符串
  i = 0;
  if (isdigit(c)) {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  // 小数点后面部分
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  s[i] = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}
