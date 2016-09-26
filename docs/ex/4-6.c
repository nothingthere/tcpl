// 加变量操作的命令。为最后打印的值添加一个变量，使用字母作为变量名

/*
实现一个变量堆，用2个等长数组记录变量和对应值

main函数循环体中，如果遇见=号，记录上一个变量名；再遇见数字时，将变量和数字同时写入变量堆

push时，如果是变量，push变量名
pop时，从变量名获取数值

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER '0'
#define MATH '1'
#define VAR '2'

double pop(void);
void push(double f);
void print_stack(void);
void duplicate_stack(void);
void swap_top(void);
void clear_stack(void);
int getop(char s[]);
void error(char *msg);

void deal_math(char s[]);
double get_var(int c);
void set_var(int name, double val);

int main(int argc, char const *argv[]) {
  int lim = 100;
  char s[lim];
  int type;
  double op2;

  while ((type = getop(s)) != EOF) {

    switch (type) {
    // 数字字符串
    case NUMBER:
      push(atof(s));
      break;
    // math.h运算
    case MATH:
      deal_math(s);
      break;
    // 变量赋值
    // 命令
    case '!':
      clear_stack();
      break;
    case '~':
      swap_top();
      break;
    case '#':
      duplicate_stack();
      break;
    case '\n':
      print_stack();
      break;
    //算术运算
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
        error("除数不能为0");
      }
      break;
    case '%':
      op2 = pop();
      if (op2 != 0.0) {
        push((int)pop() % (int)op2);
      } else {
        error("求模运算除数不能为0");
      }
      break;
    // 默认
    default:
      error("不支持此运算");
      break;
    }
  }
  return 0;
}

void error(char *msg) { printf("%s\n", msg); }

// 变量堆实现
#define VARS_SIZE 100
int vars[VARS_SIZE];
double vals[VARS_SIZE];
int var_i = 0;

int is_var(int name) {
  int i;
  for (i = 0; i < var_i; i++) {
    if (name == vars[i]) {
      return i;
    }
  }
  return -1;
}

void set_var(int name, double val) {
  int pos = is_var(name);
  if (var_i < VARS_SIZE) {
    if (pos == -1) { //变量不存在
      vars[var_i++] = name;
      vals[var_i++] = val;
      printf("新建变量%c=%.8g\n", name, val);
    } else { //变量已存在
      vals[pos] = val;
      printf("覆盖变量%c=%.8g\n", name, val);
    }
  } else {
    error("变量堆已满");
  }
}

double get_var(int name) {
  int pos = is_var(name);
  if (pos != -1) {
    return vals[pos];
  } else {
    error("无此变量");
    return 0.0;
  }
}

// 堆实现
#define STACKSIZE 100
double stack[STACKSIZE];
int stack_i = 0;
double pop(void) {
  if (stack_i > 0) {
    return stack[--stack_i];
  } else {
    error("堆已空");
    return 0.0;
  }
}

void push(double f) {
  if (stack_i < STACKSIZE)
    stack[stack_i++] = f;
  else
    error("堆已满");
}

void print_stack(void) {
  int i;
  printf("堆上的数据有：");
  for (i = 0; i < stack_i; i++) {
    printf(" %.8g", stack[i]);
  }
  printf("\n");
}

void duplicate_stack(void) {
  if (stack_i > 0) {
    push(stack[stack_i - 1]);
  } else {
    error("堆上无数据，不能复制");
  }
}

void swap_top(void) {
  double tmp1, tmp2;
  if (stack_i > 1) {
    tmp1 = pop();
    tmp2 = pop();
    push(tmp1);
    push(tmp2);
  } else {
    error("堆上数据少于2个，不能交换");
  }
}

void clear_stack(void) { stack_i = 0; }

#include <math.h>
#include <string.h>
void deal_math(char s[]) {
  double op2;
  if (strcmp(s, "sin") == 0) {
    push(sin(pop()));
  } else if (strcmp(s, "exp") == 0) {
    push(exp(pop()));
  } else if (strcmp(s, "pow") == 0) {
    op2 = pop();
    push(pow(pop(), op2));
  } else {
    error("不支持此数学运算");
  }
}

// getop实现
#include <ctype.h>
void ungetch(int c);
int getch(void);
int getop(char s[]) {
  int c, i;
  // 跳过空白字符
  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  // math.h中的函数
  i = 0;
  if (isalpha(c)) {
    while (isalpha(s[++i] = c = getch()))
      ;
    s[i] = '\0';
    if (c != EOF) {
      ungetch(c);
    }
    if (i == 1) { //变量名
      return VAR;
    } else { //数学运算
      return MATH;
    }
  }
  // 不是数字也不是负数
  if (!isdigit(c) && c != '-') {
    return c;
  }
  // 是数字
  while (isdigit(s[++i] = c = getch()))
    ;
  if (c == '.') {
    while (isdigit(s[++i] = c = getchar()))
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
#define BUFFERSIZE 100
int buffer[BUFFERSIZE];
int buffer_i = 0;
void ungetch(int c) {
  if (buffer_i < BUFFERSIZE) {
    buffer[buffer_i++] = c;
  } else {
    error("缓冲区已满");
  }
}
int getch(void) { return (buffer_i > 0) ? buffer[--buffer_i] : getchar(); }
