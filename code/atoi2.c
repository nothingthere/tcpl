/*简化版的atoi程序*/

#include <ctype.h>
#include <stdio.h>
#define MAX_LEN 1000

int get_line(char line[], int lim);
int atoi(char line[]);

int main(int argc, char const *argv[]) {
  int i;
  char line[MAX_LEN];

  while ((i = get_line(line, MAX_LEN)) > 0) {
    printf("%s --> %d\n", line, atoi(line));
  }
  return 0;
}

int atoi(char line[]) {
  int i, n, c;
  int sign;
  // 去除前置空白
  for (i = 0; isspace(line[i]); i++)
    ;

  // 获得正负号
  sign = line[i] == '-' ? -1 : 1;
  if (line[i] == '+' || line[i] == '-') {
    i++;
  }
  // 计算值
  for (n = 0; c = line[i], isdigit(c); i++) {
    n = 10 * n + (c - '0');
  }

  return n * sign;
}

int get_line(char line[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }
  // if (c == '\n') {
  //   line[i] = '\n';
  //   i++;
  // }
  line[i] = '\0';
  return i;
}
