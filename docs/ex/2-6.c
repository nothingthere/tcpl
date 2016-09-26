/*定义函数setbits(x,p,n,y)，将x上从位置p开始向右的n位，设置成y上的右n位，其它位不变，并且返回x。*/
#include <stdio.h>

unsigned int setbits(unsigned x, int p, int n, unsigned int y);

int main(int argc, char const *argv[]) {
  unsigned x = 10;
  printf("原数：%u\n", x);
  printf("结果：%u\n", setbits(x, 4, 3, 03)); // 26
  printf("结果：%u\n", setbits(x, 4, 3, 05)); // 22
  printf("结果：%u\n", setbits(x, 4, 3, 07)); // 30

  return 0;
}
/*
1. 获取y上的后n位，其它位置于0，再移动到需设置的位
  (~(~0 << n) & y) << (p + 1 - n)
2. 用0mask掉x上需要设置的所有位, 即掏空X上需要设置的位（都设置称0）
        111000111形式

    AND
  x
3. 将两者取OR
*/
unsigned setbits(unsigned x, int p, int n, unsigned int y) {
  unsigned int padding = p + 1 - n;                  /*右边不动的位数*/
  unsigned int target = (~(~0 << n) & y) << padding; /* #1*/
  unsigned int empty = ((~0 << (p + 1)) | ~(~0 << padding)) & x; /*#2掏空*/
  return target | empty;
}
