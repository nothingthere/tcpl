#include "calc.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100 //操作符号或数字的字符的最大长度

int main(void) {
  int type;
  double op2;
  char s[MAXOP];
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER: //遇见数字字符串时
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0) {
        push(pop() / op2);
      } else {
        printf("error:除数不能为0\n");
      }
      break;
    case '\n': //显示结果
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error:不支出此类计算：'%c'\n", type);
      break;
    }
  }
  return 0;
}
