/*定义函数rightrot(x,n)函数，将x上右边n位反转，并返回x。其它位不变。*/

#include <stdio.h>

unsigned int getbits(unsigned x, int p, int n);
unsigned int setbits(unsigned x, int p, int n, unsigned int y);
unsigned int rightrot(unsigned x, int n);

int main(int argc, char const *argv[]) {
  unsigned x = 10;
  printf("原数：%u\n", x);
  printf("结果：%u\n", rightrot(x, 3)); // 10
  printf("结果：%u\n", rightrot(x, 4)); // 5
  printf("结果：%u\n", rightrot(x, 5)); // 10
  printf("结果：%u\n", rightrot(x, 6)); // 20
  return 0;
}

/*
相当于字符串反转
*/
unsigned rightrot(unsigned x, int n) {
  unsigned int temp_left, temp_right;
  int i;
  for (i = 0; i < n; i++, n--) {
    temp_right = getbits(x, i, 1);    /*右边一位*/
    temp_left = getbits(x, n - 1, 1); /*左边一位*/
    // printf("i=%d n-1=%d\n", i, n - 1);
    // printf("temp_left: %u  temp_right: %u\n", temp_left, temp_right);
    // printf("x=%u\n", x);
    x = setbits(x, i, 1, temp_left);
    x = setbits(x, n - 1, 1, temp_right);
  }
  return x;
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
