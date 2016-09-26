// 扩展逆波兰计算器，增加求模运算（%），并支持负数。
#include <stdio.h>
#include <stdlib.h> //atof(s)

#define NUMBER '0' //获得数字的信号

int getop(char s[]);
double pop(void);
void push(double f);

int main(int argc, char const *argv[]) {
  int max_ops = 100; //一个操作符的最大长度
  char s[max_ops];
  int type;
  double op2;
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
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
      if (op2 != 0.0) {
        push(pop() / op2);
      } else {
        printf("error：除数不能为0\n");
      }
      break;
    case '%': //求模运算只支持整数
      op2 = pop();
      if (op2 != 0.0) {
        push((int)pop() % (int)op2);
      } else {
        printf("error：求模运算除数不能为0\n");
      }
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error：不支持‘%c’运算\n", type);
      break;
    }
  }
  return 0;
}

//堆实现
#define STACK_SIZE 100
double stack[STACK_SIZE];
int stack_i = 0;

void push(double f) {
  if (stack_i < STACK_SIZE) {
    stack[stack_i++] = f;
  } else {
    printf("error：堆已满\n");
  }
}

double pop(void) {
  if (stack_i > 0) {
    return stack[--stack_i];
  } else {
    printf("error：堆已空\n");
    return 0.0;
  }
}
// getop实现，支持负数

#include <ctype.h>

void ungetch(int c);
int getch(void);
int getop(char s[]) {
  int c, i;
  // 跳过空字符
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  // 如果不是数字 且不是负号
  if (!isdigit(c) && c != '-') {
    s[1] = '\0';
    return c;
  }
  //如果是数字
  i = 0;
  while (isdigit(s[++i] = c = getch()))
    ;
  //小数部分
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()))
      ;
  }

  s[i] = '\0';

  if (c != EOF) {
    ungetch(c);
  }

  // 如果是单独的减法运算符号
  if (i == 1 && s[0] == '-') {
    // printf("SHIT\n");
    return '-';
  }

  return NUMBER;
}

//缓冲区实现
#define BUFFER_SIZE 100
int buffer[BUFFER_SIZE];
int buffer_i = 0;

void ungetch(int c) {
  if (buffer_i < BUFFER_SIZE) {
    buffer[buffer_i++] = c;
  } else {
    printf("缓冲区已满\n");
  }
}

int getch(void) { return buffer_i > 0 ? buffer[--buffer_i] : getchar(); }
