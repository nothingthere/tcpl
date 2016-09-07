/*代码重复太多，应该可以使用宏，将代码简化*/

#include <float.h>
#include <limits.h>
#include <stdio.h>

struct range {
  long double min;  /*最小值*/
  long double max;  /*最大值*/
  long double umax; /*无符号最大值*/
};

struct range CHAR_RANGE;
struct range SHORT_RANGE;
struct range INT_RANGE;
struct range LONG_RANGE;

/*打印范围*/
void show_range(struct range, char *msg);

/*字符型系统和手动计算取值范围*/
struct range sys_char_range(void);
void handle_char_range(void);
void handle_char_range(void);
void handle_char_range2(void);

/*短整型系统和手动计算取值范围*/
struct range sys_short_range(void);
void handle_short_range(void);
void handle_short_range2(void);

/*整型系统和手动计算取值范围*/
struct range sys_int_range(void);
void handle_int_range(void);
void handle_int_range2(void);

/*长整型系统和手动计算取值范围*/
struct range sys_long_range(void);
void handle_long_range(void);
void handle_long_range2(void);

/*显示各类型结果*/
void show_char_range(void);
void show_short_range(void);
void show_int_range(void);
void show_long_range(void);

int main(int argc, char const *argv[]) {
  show_char_range();
  show_short_range();
  show_int_range();
  show_long_range();
  return 0;
}

void show_range(struct range range, char *msg) {
  printf("%s：\n", msg);
  printf("有符号取值范围：%.0Lf --- %.0Lf\n", range.min, range.max);
  printf("无符号取值范围：0 --- %.0Lf\n", range.umax);
}

void show_char_range(void) {
  printf("\n字符型：\n");
  show_range(sys_char_range(), "系统定义");
  handle_char_range2();
  show_range(CHAR_RANGE, "手动计算");
}
void show_short_range(void) {
  printf("\n短整型：\n");
  show_range(sys_short_range(), "系统定义");
  handle_short_range2();
  show_range(SHORT_RANGE, "手动计算");
}
void show_int_range(void) {
  printf("\n整型\n");
  show_range(sys_int_range(), "系统定义");
  handle_int_range2();
  show_range(INT_RANGE, "手动计算");
}
//
void show_long_range(void) {
  printf("\n长整型\n");
  show_range(sys_long_range(), "系统定义");
  handle_long_range2();
  show_range(LONG_RANGE, "手动计算");
}

/*--------------------------------
采用位运算，速度超快！！！
利用数字常量的， 位运算结果，在赋值时强制类型转换
注意：数字常量的默认类型为整型，所以在计算长整型long时，需在数字后加“l”，如“1l”。
*/
void handle_char_range2(void) {
  // long min, max, umax;
  long size = sizeof(char) * CHAR_BIT;
  char min, max;
  unsigned char umax;
  min = (1 << (size - 1));
  max = ((1 << (size - 1)) - 1);
  umax = (~0);
  CHAR_RANGE.min = min;
  CHAR_RANGE.max = max;
  CHAR_RANGE.umax = umax;
}

void handle_short_range2(void) {
  long min, max, umax;
  long size = sizeof(short) * CHAR_BIT;
  min = (short)(1 << (size - 1));
  max = (short)((1 << (size - 1)) - 1);
  umax = (unsigned short)(~0);
  SHORT_RANGE.min = min;
  SHORT_RANGE.max = max;
  SHORT_RANGE.umax = umax;
}

void handle_int_range2(void) {
  long min, max, umax;
  long size = sizeof(int) * CHAR_BIT;
  // printf("%ld\n", size);

  min = (1 << (size - 1));
  max = ((1 << (size - 1)) - 1);
  umax = (unsigned int)(~0);
  INT_RANGE.min = min;
  INT_RANGE.max = max;
  INT_RANGE.umax = umax;
}

void handle_long_range2(void) {
  long double min, max, umax;
  long size = sizeof(long) * CHAR_BIT;
  // printf("%ld\n", size);
  /*数字常量默认的类型为整型：int*/
  min = (long)(1l << (size - 1));
  max = (long)((1l << (size - 1)) + 1);
  umax = (unsigned long)(~0);
  LONG_RANGE.min = min;
  LONG_RANGE.max = max;
  LONG_RANGE.umax = umax;
}

/*--------------------------------
手动计算，计算长整型太耗时，测试长整型计算结果的时间可以睡一觉（没测试，懒得等）
实现原理：某类型数值最大值再+1，将得到最小值；如果无符号unsigned，最大值加1，得到0
速度优化方案：
1.
将各类型取值范围声明为全局变量，计算后缓存
2.
位数多的类型，利用位数���的类型的计算结果，避免重复计算，如int类型利用short类型的计算结果。注意：为防止相邻类型（如short和int）位数一样，利用低类型的结果时，最大值需-1，最小值需+1。
*/
/*计算字符型*/
struct range sys_char_range(void) {
  struct range range;
  range.min = CHAR_MIN;
  range.max = CHAR_MAX;
  range.umax = UCHAR_MAX;
  return range;
}

void handle_char_range(void) {
  unsigned char ubase;
  char base;
  long min, max, umax;
  long i;
  for (i = 0, base = 0;; i++, base++) {
    if (base < 0) {
      max = i - 1;
      min = base;
      break;
    }
  }

  for (i = max, ubase = max;; i++, ubase++) {
    if (i != 0 && ubase == 0) {
      umax = i - 1;
      break;
    }
  }

  // for (i = 0, base = 0;; i--, base--) {
  //   if (base > 0) {
  //     min = i + 1;
  //     break;
  //   }
  // }
  // printf("%ld %ld %ld\n", min, max, umax);
  CHAR_RANGE.min = min;
  CHAR_RANGE.max = max;
  CHAR_RANGE.umax = umax;
}

/*计算短整型
利用字符型结果*/
struct range sys_short_range(void) {
  struct range range;
  range.min = SHRT_MIN;
  range.max = SHRT_MAX;
  range.umax = USHRT_MAX;
  return range;
}

void handle_short_range(void) {
  long min, max, umax;
  short base;
  unsigned short ubase;
  long i;

  if (CHAR_RANGE.max == 0) { /*防止单独调用，还没计算字符串取值范围*/
    handle_char_range();
  }
  for (i = CHAR_RANGE.max - 1, base = CHAR_RANGE.max - 1;; i++, base++) {
    if (base < 0) {
      max = i - 1;
      min = base;
      break;
    }
  }

  for (i = max, ubase = max;; i++, ubase++) {
    // printf("i=%d base=%d\n", i, ubase);
    if (ubase == 0) {
      umax = i - 1;
      break;
    }
  }

  // for (i = CHAR_RANGE.min + 1, base = CHAR_RANGE.min + 1;; i--, base--) {
  //   if (base > 0) {
  //     min = i + 1;
  //     break;
  //   }
  // }

  SHORT_RANGE.min = min;
  SHORT_RANGE.max = max;
  SHORT_RANGE.umax = umax;
}
/*计算整型
利用短整型结果*/

struct range sys_int_range(void) {
  struct range range;
  range.min = INT_MIN;
  range.max = INT_MAX;
  range.umax = UINT_MAX;
  return range;
}

void handle_int_range(void) {
  long min, max, umax;
  int base;
  unsigned int ubase;
  long i;
  //
  if (SHORT_RANGE.max == 0) { /*防止单独调用，还没计算短整型范围*/
    handle_short_range();
  }

  for (i = SHORT_RANGE.max - 1, base = SHORT_RANGE.max - 1;; i++, base++) {
    if (base < 0) {
      max = i - 1;
      min = base;
      break;
    }
  }

  for (i = max, ubase = max;; i++, ubase++) {
    // printf("i=%d base=%d\n", i, ubase);
    if (ubase == 0) {
      umax = i - 1;
      break;
    }
  }
  // // umax = 1 << (sizeof(int) * 7);
  // for (i = SHORT_RANGE.min + 1, base = SHORT_RANGE.min + 1;; i--, base--) {
  //   if (base > 0) {
  //     min = i + 1;
  //     break;
  //   }
  // }

  INT_RANGE.min = min;
  INT_RANGE.max = max;
  INT_RANGE.umax = umax;
  // printf("int umax:%lu", umax);
}

/*计算长整型
利用整型结果*/

struct range sys_long_range(void) {
  struct range range;
  range.min = LONG_MIN;
  range.max = LONG_MAX;
  range.umax = ULONG_MAX;
  return range;
}

void handle_long_range(void) {
  long min, max, umax;
  long base;
  unsigned long ubase;
  double i;
  //
  if (INT_RANGE.max == 0) { /*防止单独调用，还没计算短整型范围*/
    handle_int_range();
  }

  for (i = INT_RANGE.max - 1, base = INT_RANGE.max - 1;; i++, base++) {
    if (base < 0) {
      max = i - 1;
      min = base;
      break;
    }
  }

  for (i = max, ubase = max;; i++, ubase++) {
    // printf("i=%d base=%d\n", i, ubase);
    if (ubase == 0) {
      umax = i - 1;
      break;
    }
  }
  // umax = 1 << (sizeof(int) * 7);
  // for (i = INT_RANGE.min + 1, base = INT_RANGE.min + 1;; i--, base--) {
  //   if (base > 0) {
  //     min = i + 1;
  //     break;
  //   }
  // }

  INT_RANGE.min = min;
  INT_RANGE.max = max;
  INT_RANGE.umax = umax;
  // printf("int umax:%lu", umax);
}
