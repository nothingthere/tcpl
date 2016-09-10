/*定义函数itob(n, s, b)，将整数n转换为字符串s，以b为基数。
如itob(n, s, 16)，将n转换为16进制表示的字符串s。*/

/*
与atoi的唯一不同就是将基数10，变为不同的基数。
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void itob(int n, char s[], int base);
void reverse(char s[]);
int abse(int x);

int main(int argc, char const *argv[]) {
  // 测试整数
  int nums[] = {0, INT_MIN, INT_MAX};
  int count = 3;

  // 进制
  int bases[] = {2, 8, 10, 16};
  int bases_count = 4;

  int i, j;
  char line[(sizeof(int) * 8) + 1 + 2];

  for (i = 0; i < count; i++) { /*历遍每个数字*/
    printf("%d\n", nums[i]);
    for (j = 0; j < bases_count; j++) { /*历遍每个基数*/
      itob(nums[i], line, bases[j]);
      printf("%4d: %s\n", bases[j], line);
    }
    printf("-----------\n");
  }
  return 0;
}

void itob(int n, char s[], int base) {
  int sign; /*正负号*/
  int i;    /*s下标*/
  int tmp;  /*数字中间量*/
  sign = n < 0 ? -1 : 1;
  // 开始写入
  i = 0;
  do {
    tmp = abs(n % base);
    if (tmp > 9) {
      tmp = (tmp - 10) + 'a';
    } else {
      tmp += '0';
    }
    s[i++] = tmp;
  } while (n /= base);

  // 对8进制和16进制添加前缀
  if (base == 8) {
    s[i++] = '0';
  }
  if (base == 16) {
    s[i++] = 'X';
    s[i++] = '0';
  }
  // 添加符号，只有二进制无正负号
  if (base != 2) {
    if (sign < 0) {
      s[i++] = '-';
    }
  }

  s[i] = '\0';
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
