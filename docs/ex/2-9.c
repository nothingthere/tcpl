/*在（two's complement）数字系统中，`x &= (x -
 * 1)`可去除最有端为1的位。解释原因，并利用此特点重写bitcount函数，使其速度更快。*/

/*
原因：x -
1，实际上是将最右一位的1变为0，其往右的所有位（0）都变为1。再与其自身使用AND操作，就去掉了最右一位的1。
*/
#include <stdio.h>

int bitcount(unsigned int x);
int main(int argc, char const *argv[]) {
  int x1 = 01;
  int x2 = 03;
  int x3 = 07;
  printf("%d: %d\n", x1, bitcount(x1));
  printf("%d: %d\n", x2, bitcount(x2));
  printf("%d: %d\n", x3, bitcount(x3));
  return 0;
}

int bitcount(unsigned int x) {
  int b;
  for (b = 0; x != 0; x &= (x - 1)) {
    b++;
  }
  return b;
}
