// 为计算器增加命令功能，不pop，只打印堆上的数据；复制堆上的数据；交换顶端两个数据；清空整个堆。

#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'

int getop(char s[]);
void push(double f);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

void error(char *msg);

int main(int argc, char const *argv[]) {
  int lim = 100;
  char s[lim];
  int type;
  double op2;
  while ((type = getop(s)) != EOF) {
    switch (type) {
    // 数字
    case NUMBER:
      push(atof(s));
      break;
    // 运算符号
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
        error("被除数不能为0");
      }
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0) {
        push((int)pop() % (int)op2);
      } else {
        error("求模运算被除数不能为0");
      }
      break;
    // case '\n':
    // printf("\n\t %.8g\n", pop());
    // print_top();
    // break;
    // 命令
    // 1.打印堆上顶端的数据
    case '\n':
      print_top();
      break;
    // 2.复制堆上最顶端的数据
    case '#':
      duplicate_top();
      break;
    // 3.交换堆上最顶端的两个数据
    case '~':
      swap_top();
      break;
    // 4.清除堆
    case '!':
      clear_stack();
      break;
    // 5.退出
    case 'q':
      printf("bey!\n");
      exit(0);
      break;
    //默认
    default:
      error("运算不支持");
      break;
    }
  }
  return 0;
}

void error(char *s) { printf("%s\n", s); }
// 堆实现
#define STACK_SIZE 100
double stack[STACK_SIZE];
int stack_i = 0;
void push(double f) {
  // printf("push\n");
  if (stack_i < STACK_SIZE) {
    stack[stack_i++] = f;
  } else {
    error("堆已满");
  }
}

double pop(void) {
  // printf("pop\n");
  if (stack_i > 0) {
    return stack[--stack_i];
  } else {
    error("堆已空");
    return 0.0;
  }
}

void print_top(void) {
  printf("堆上数据有：");
  int i;
  for (i = 0; i < stack_i; i++) {
    printf(" %.8g", stack[i]);
  }
  printf("\n");
}

// 复制堆上最顶端的数据
void duplicate_top(void) {
  if (stack_i < STACK_SIZE && stack_i > 0) {
    push(stack[stack_i - 1]);
    printf("复制顶端成功\n");
  } else {
    error("复制失败");
  }
}

// 交换堆上最顶端的两个数据
void swap_top(void) {
  double tmp;
  if (stack_i >= 2) {
    tmp = stack[stack_i - 1];
    stack[stack_i - 1] = stack[stack_i - 2];
    stack[stack_i - 2] = tmp;
    printf("交换顶端成功\n");

  } else {
    error("交换失败，堆上的数据少于2个\n");
  }
}

// 清除堆
void clear_stack(void) {
  stack_i = 0;
  printf("堆已清除\n");
}

// getop实现
#include <ctype.h>
void ungetch(int c);
int getch(void);

int getop(char s[]) {
  int c, i;
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  // 不为数字且不是-
  if (!isdigit(c) && c != '-') {
    s[1] = '\0';
    return c;
  }
  // 数字
  i = 0;
  while (isdigit(s[++i] = c = getch()))
    ;
  if (c == '.') {
    while (isdigit(s[++i] = c = getch()))
      ;
  }
  s[i] = '\0';
  if (c != EOF) {
    ungetch(c);
  }

  // 单独的-号
  if (i == 1 && s[0] == '-') {
    return '-';
  }

  return NUMBER;
}
// 缓冲区实现
#define BUFFSIZE 100
int buffer[BUFFSIZE];
int buff_i = 0;

int getch(void) { return buff_i > 0 ? buffer[--buff_i] : getchar(); }

void ungetch(int c) {
  if (buff_i < BUFFSIZE) {
    buffer[buff_i++] = c;
  } else {
    error("缓冲区已满");
  }
}
