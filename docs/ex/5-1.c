/*getint函数将后面没跟任何数字的+和-号默认为0，修改函数将+和-字符push回去。*/

#include <ctype.h>
#include <stdio.h>

int getint(int *pn);
void ungetch(int c);
int getch(void);

int main(int argc, char const *argv[]) {
  int count = 3;
  int nums[count];
  int i;
  printf("请输入3个整数：\n");
  for (i = 0; i < count && getint(&nums[i]) != EOF; i++)
    ;
  // 输出
  for (i = 0; i < count; i++) {
    printf("%d\n", nums[i]);
  }

  return 0;
}

int getint(int *pn) {
  int c;
  int sign;
  int minus_or_plus;
  // 跳过空格
  while (isspace(c = getch()))
    ;
  // 不是数字，返回
  if (!isdigit(c) && c != '+' && c != '-') {
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

  if (!isdigit(c)) {
    if (minus_or_plus) {
      ungetch(sign < 0 ? '-' : '+');
    }
    ungetch(c);
    return 0;
  }
  // 练习题新加结束
  // 获取数值
  for (*pn = 0; isdigit(c); c = getch()) {
    *pn = (*pn * 10) + (c - '0');
  }

  *pn *= sign;
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
