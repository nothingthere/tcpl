#include "calc.h"
#include <stdio.h>
// 堆实现
#define MAXVAL 100  //堆上最多能有多少个数字
int sp = 0;         //堆的当前索引
double val[MAXVAL]; //堆

void push(double f) {
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else {
    printf("error：堆已满\n");
  }
}

double pop(void) {
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error：堆上无任何数据\n");
    return 0.0;
  }
}
