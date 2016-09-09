/*定义invert(x,p,n)函数，将x上从位置p开始向右的n位置反（1变为0,0变为1），并且返回x。其它位不变。*/

#include <stdio.h>

unsigned int getbits(unsigned x, int p, int n);
unsigned int setbits(unsigned x, int p, int n, unsigned int y);
unsigned int invert(unsigned x, int p, int n);

int main(int argc, char const *argv[]) {
  unsigned x = 10;
  printf("原数：%u\n", x);
  printf("结果：%u\n", invert(x, 3, 3)); // 15
  printf("结果：%u\n", invert(x, 4, 3)); // 22
  printf("结果：%u\n", invert(x, 5, 3)); // 50
  return 0;
}

/*
取反 > getbits > setbits

*/
unsigned invert(unsigned x, int p, int n) {

  return setbits(x, p, n, getbits(~x, p, n));
}

unsigned getbits(unsigned x, int p, int n) {
  return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned setbits(unsigned x, int p, int n, unsigned int y) {
  unsigned int padding = p + 1 - n;                  /*右边不动的位数*/
  unsigned int target = (~(~0 << n) & y) << padding; /* 1*/
  unsigned int empty = ((~0 << (p + 1)) | ~(~0 << padding)) & x; /*2掏空*/
  return target | empty;
}
