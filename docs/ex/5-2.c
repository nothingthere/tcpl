/*模范getfloat函数定义getfloat函数。getfloat函数的返回值应该为何种类型。*/

/*
由于需返回EOF,还是应该返回整型
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>

int getfloat(float *pn);
void ungetch(int c);
int getch(void);

int main(int argc, char const *argv[]) {
  int count = 3;
  float nums[count];
  int i;
  printf("请输入3个整数：\n");
  for (i = 0; i < count && getfloat(&nums[i]) != EOF; i++)
    ;
  // 输出
  printf("输出\n");
  for (i = 0; i < count; i++) {
    printf("%.8g\n", nums[i]);
  }

  return 0;
}

int getfloat(float *pn) {
  int c;
  int sign;
  int minus_or_plus;
  float dec = 1.0f; /*小数点后面的倍数*/
  int power = 0.0f; /*科学计数10的次方值*/
  // 跳过空格
  while (isspace(c = getch()))
    ;
  // 不是数字，返回
  if (!isdigit(c) && c != '+' && c != '-' && c != '.') {
    ungetch(c);
    return 0;
  }
  // 确定正负号
  sign = c == '-' ? -1 : 1;
  // 跳过正负号
  if (c == '+' || c == '-') {
    c = getch();
    minus_or_plus = 1;
  }
  // 练习题新加

  if (!isdigit(c) && c != '.') {
    if (minus_or_plus) {
      ungetch(sign < 0 ? '-' : '+');
    }
    ungetch(c);
    return 0;
  }
  // 练习题新加结束
  // 获取数值
  for (*pn = 0.0f; isdigit(c); c = getch()) {
    *pn = (*pn * 10) + (c - '0');
  }

  // 获取小数点后面数值
  if (c == '.') {
    c = getch();
    while (isdigit(c)) {
      dec *= 10;
      *pn = (*pn * 10) + (c - '0');
      c = getch();
    }
  }
  // 获取科学计数法数值
  if (c == 'e' || c == 'E') {
    int power_sign;
    c = getch();
    power_sign = c == '-' ? -1 : 1;
    if (c == '-' || c == '+') {
      c = getch();
    }
    while (isdigit(c)) {
      power = (power * 10) + (c - '0');
      c = getch();
    }
    power *= power_sign;
  }

  // 计算结果
  *pn *= sign;
  *pn /= dec;
  *pn = *pn * pow(10, power);
  if (c != EOF) {
    ungetch(c);
  }
  // 正常返回
  return c;
}

// 缓存实现
#define BUFFSIZE 100
int buffer[BUFFSIZE];
int buffer_i = 0;
int getch(void) { return buffer_i > 0 ? buffer[--buffer_i] : getchar(); }
void ungetch(int c) {
  if (buffer_i < BUFFSIZE) {
    buffer[buffer_i++] = c;
  } else {
    printf("缓存已满\n");
  }
}
