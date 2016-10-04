/*编写expr程序，利用命令行参数实现逆波兰计算器，每个操作数和操作符号都是一个参数。
如`expr 2 3 4 + ''*''`会转换为`2*(3+4)`计算得出结果。

注意：UNIX命令行参数膨胀

*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h> /*for atof*/
#define NUMBER '0'
#define MAXOP 100 /*操作数和操作符号最大长度*/

int getop(const char *s);
void push(double f);
double pop(void);

/*
历遍所有参数
历遍过程中进行pop和push
*/
int main(int argc, char const *argv[]) {
  int type;
  double op2;
  while (--argc > 0) {
    ++argv;
    // printf("%s\n", *agv);
    type = getop(*argv);
    switch (type) {
    case NUMBER:
      push(atof(*argv));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '*':
      push(pop() * pop());
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error：除数不能为0\n");
      break;
    default:
      printf("不支持运算：%c\n", type);
      break;
    }
  }
  printf("\t%.8g\n", pop());
  return 0;
}

// getop实现

int getop(const char *s) {
  int c; /*字符中间变量*/
  // 以正负号开始
  c = *s++;
  // 只是正负号
  if (!isdigit(c) && !isdigit(*s))
    return c;
  // 只是其他符号
  // 运算符号
  // 数字收集
  return NUMBER;
}

// 堆实现:指针版本
#define STACKSIZE 100
double stack[STACKSIZE];
double *stack_p = stack;
double pop(void) {
  if (stack_p > stack) {
    return *--stack_p;
  } else {
    printf("error：堆内无数据\n");
    return 0.0;
  }
}
void push(double f) {
  // printf("push:%.8g\n", f);
  if (stack_p > stack + STACKSIZE) {
    printf("error：堆已经满\n");
  } else {
    *stack_p++ = f;
  }
}
