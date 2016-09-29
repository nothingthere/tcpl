/*模仿printd函数，定义递归版本的itoa函数。即使用递归将整数转换为字符串。*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void i2a(int i, char s[]);

int main(int argc, char const *argv[]) {
  int nums[] = {123, 0, -2323, INT_MIN, INT_MAX};
  int count = 5;
  char line[22];
  int i;
  for (i = 0; i < count; i++) {
    i2a(nums[i], line);
    printf("%11d: %s\n", nums[i], line);
  }
  return 0;
}
//
// void i2a_help(int n, char s[], int i) {
//   if (n / 10) {
//     i2a_help(abs(n / 10), s, i + 1);
//   }
//   s[i] = abs(n % 10) + '0';
//   putchar(s[i]);
// }
//
// void i2a(int n, char s[]) {
//   int i = 0;
//   if (n < 0) {
//     s[i++] = '-';
//   }
//   i2a_help(n, s, i);
// }
