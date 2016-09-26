//逆波兰计算器

#include <stdio.h>
#include <stdlib.h> //使用atof()函数

#define MAXOP 100  //操作符号或数字的字符的最大长度
#define NUMBER '0' //输入内容为数字的信号

int getop(char[]);
void push(double);
double pop(void);

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

// 堆实现
#define MAXVAL 100  //堆上最多能有多少个数字
int sp = 0;         //堆的当前索引
double val[MAXVAL]; //堆

void push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else {
    printf("error：堆已满\n");
  }
}

double pop(void) {
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error：堆上无任何数据\n");
    return 0.0;
  }
}

// getop实现
#include <ctype.h>
void ungetch(int c);
int getch(void);

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

#define BUFFERSIZE 100
int buffer[BUFFERSIZE];
int bufp = 0;

int getch(void) { return (bufp > 0) ? buffer[--bufp] : getchar(); }
void ungetch(int c) {
  if (bufp < BUFFERSIZE) {
    buffer[bufp++] = c;
  } else {
    printf("error：buffer已满\n");
  }
}
