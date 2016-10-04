/*
month_name(n)：根据月份返回对应月份名称
重点：使用函数内静态变量，当函数调用完毕后，依然能获取指针对应内存。
？？？：为啥子不适用static静态变量也能行？？
*/

#include <stdio.h>
#include <string.h>

char *month_name(int n);

int main(int argc, char const *argv[]) {
  int i;
  char *p;
  // char m[] = "i have";
  // char *n = " a dream!";
  // printf("%p\n", m);
  // printf("%p\n", strcat(m, n));

  for (i = 0; i < 13; i++) {
    p = month_name(i);
    // strcat(p, "月");

    printf("%s月\n", p);
  }
  return 0;
}

char *month_name(int n) {

  static char *names[] = {"非法", "一", "二", "三", "四",   "五",  "六",
                          "七",   "八", "九", "十", "十一", "十二"};

  return (n >= 1 && n <= 12) ? names[n] : names[0];
}
