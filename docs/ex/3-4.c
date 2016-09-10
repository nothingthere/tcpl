/*上述程序在two's complement数字表示系统中，不能处理最小负数的情况。
解释原因，并重写此函数，解决兼容性问题。*/

/*
不能处理最小负数的原因：
    最小负数取反是其本身
    abs(n) % 10函数也不能解决这个问题，因为最小负数的abs值还是其本身

解决方法：
        使用abs(n % 10) + '0'
        控制循环的语句(n /= 10)>0改为(n /= 10)，后者最终会等于0
*/

#include <limits.h>
#include <stdio.h>

int abs(int x);
void itoa(int n, char s[]);
void reverse(char line[]);

int main(int argc, char const *argv[]) {
  int nums[] = {INT_MIN, INT_MAX};
  // printf("%d\n", abs(INT_MIN % 10));
  int count = 2;
  char line[10 + 1 + 1];
  int i;
  for (i = 0; i < count; i++) {
    itoa(nums[i], line);
    printf("%d: %s\n", nums[i], line);
  }
  return 0;
}

void itoa(int n, char s[]) {
  int i, sign;
  // 开始写入字符串
  sign = n >= 0 ? 1 : -1;
  i = 0;
  do {
    s[i++] = abs(n % 10) + '0';
  } while (n /= 10);
  // 添加正负号

  if (sign < 0) {
    s[i++] = '-';
  }
  // 结尾字符串
  s[i] = '\0';
  // 颠倒
  reverse(s);
}

int abs(int x) { return x < 0 ? -x : x; }

void reverse(char line[]) {
  int n; /*长度*/
  int i, j;
  // 先获取长度,长度为n
  for (n = 0; line[n] != '\0'; n++)
    ;
  // 前后交换
  for (i = 0, j = n - 1; i < j; i++, j--) {
    // 利用位运算交换值
    line[i] ^= line[j] ^= line[i] ^= line[j];
  }
}
