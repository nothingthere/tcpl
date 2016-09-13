/*简化版atof(s)函数*/

#include <ctype.h>
#include <stdio.h>

#define MAX_LINE 100

int main(int argc, char const *argv[]) {
  double sum, atof(char s[]);
  int atoi(char s[]);

  char line[MAX_LINE];
  int get_line(char line[], int max);

  sum = 0;
  while (get_line(line, MAX_LINE) > 0) {
    printf("\t%g\n", sum += atoi(line));
  }
  return 0;
}

double atof(char s[]) {
  double val, power;
  int i, sign;

  // 跳过空格
  for (i = 0; isspace(s[i]); i++)
    ;

  // 确定正负号
  sign = (s[i] == '-') ? -1 : 1;

  if (s[i] == '-' || s[i] == '+') {
    i++;
  }

  // 处理小数点前面部分
  for (val = 0.0; isdigit(s[i]); i++) {
    val = val * 10.0 + (s[i] - '0');
  }

  //处理小数点后面部分
  if (s[i] == '.') {
    i++;
  }
  for (power = 1.0; isdigit(s[i]); i++) {
    val = val * 10.0 + (s[i] - '0');
    power *= 10.0;
  }

  // 返回
  return (val * sign) / power;
}

int atoi(char line[]) { return (int)atof(line); }

int get_line(char line[], int lim) {
  int i, c;
  i = 0;
  while (--lim && (c = getchar()) != EOF && c != '\n') {
    line[i++] = c;
  }

  if (c == '\n') {
    line[i++] = c;
  }

  line[i] = '\0';

  return i;
}
