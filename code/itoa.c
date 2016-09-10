/*将数字转换为字符串*/

#include <limits.h>
#include <stdio.h>

void itoa(int n, char s[]);
void reverse(char line[]);

int main(int argc, char const *argv[]) {
  // 测试reverse函数
  char name[] = "claudio";
  printf("原名字：%s\n", name);
  reverse(name);
  printf("名字颠倒后：%s\n", name);
  // printf("%lu\n", ULONG_MAX); //获取long型最大长度20
  // 测试itoa函数
  int nums[] = {0, 1212313, -2323, INT_MIN, INT_MAX};
  int count = 5;
  char line[20 + 1 + 1];
  int i;
  for (i = 0; i < count; i++) {
    itoa(nums[i], line);
    printf("%d: %s\n", nums[i], line);
  }
  return 0;
}

void itoa(int n, char s[]) {
  int i, sign;
  // 将负数转换为正数，并获取正负号
  if ((sign = n) < 0) {
    n = -n;
  }
  // 开始写入字符串
  i = 0;
  do {
    s[i++] = (n % 10) + '0';
  } while ((n = n / 10) > 0);
  // 添加正负号
  if (sign < 0) {
    s[i++] = '-';
  }
  // 结尾字符串
  s[i] = '\0';
  // 颠倒
  reverse(s);
}
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
