/*将十进制数以字符串形式输出*/
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void printd(int n);

int main(int argc, char const *argv[]) {
  int i;

  int nums[] = {-10, 12345, INT_MIN, INT_MAX};
  for (i = 0; i < (sizeof(nums) / sizeof(int)); i++) {
    printd(nums[i]);
    printf("\n");
  }

  return 0;
}

void printd(int n) {
  if (n < 0) {
    putchar('-');
  }

  if (n / 10) {
    printd(abs(n / 10));
  }
  putchar(abs(n % 10) + '0');
}
