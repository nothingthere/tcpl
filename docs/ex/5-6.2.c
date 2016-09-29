/*指针版atoi
将字符串转换为整数
*/

#include <ctype.h>
#include <stdio.h>

int atoi(char *s);

int main(int argc, char const *argv[]) {
  char *lines[] = {"", "a1", "12.2", "-21d", "  12.e"};
  int count = 5;
  int i;
  for (i = 0; i < count; i++) {
    printf("\"%6s\" -> %d\n", lines[i], atoi(lines[i]));
  }
  // printf("%d\n", atoi("-1"));
  return 0;
}

int atoi(char *s) {
  int sign;
  int n = 0;
  // 跳过空格
  while (isspace(*s)) /*不能使用*s++，原因为即使当前字符不是空格，还会自增*/
    s++;
  // 获取符号
  sign = *s == '-' ? -1 : 1;
  if (*s == '+' || *s == '-')
    s++;
  // 获取整数
  while (isdigit(*s)) {
    // printf("*s=%c\n", *s);
    n = n * 10 + (*s - '0');
    s++;
  }
  // 返回
  return n * sign;
}
