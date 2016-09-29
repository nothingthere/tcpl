/*指针版getop*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'
#define MAXOP 100

int getop(char *s);
double pop(void);
void push(double);
int main(int argc, char const *argv[]) {
  char line[MAXOP];
  int type;
  double op2;
  while ((type = getop(line)) != EOF) {
    // printf("type=%c\n", type);
    switch (type) {
    case NUMBER:
      push(atof(line));
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
        printf("除数不能为0\n");
      }
      break;
    case '\n':
      // printf("!!!!\n");
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("不支持运算：%c\n", type);
      break;
    }
  }
  return 0;
}

// 堆实现
#define STACK_SIZE 100
double stack[STACK_SIZE];
int stack_i = 0;
void push(double f) {
  if (stack_i < STACK_SIZE)
    stack[stack_i++] = f;
  else
    printf("堆已满\n");
}

double pop(void) {
  if (stack_i > 0)
    return stack[--stack_i];
  else {
    printf("堆已空\n");
    return 0.0;
  }
}

// 缓存器实现
#define BUFFSIZE 100
int buff[BUFFSIZE];
int buff_i = 0;

int getch(void) { return buff_i > 0 ? buff[--buff_i] : getchar(); }
void ungetch(int c) {
  if (buff_i < BUFFSIZE) {
    buff[buff_i++] = c;
  } else {
    printf("缓存区已满\n");
  }
}
// getop实现
int getop(char *s) {
  int c;
  // 跳过空格
  while ((*s = c = getch()) == ' ' || c == '\t')
    ;
  // s++;
  *++s = '\0';

  // 不是数字
  if (!isdigit(c)) {
    // printf("不是数字\n");
    return c;
  }
  // 是数字，收集
  while (isdigit(*s++ = c = getch())) {
    // s++;
  }
  // 小数点
  // 返回
  *s = '\0';
  if (c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}

int getop2(char s[]) {
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
