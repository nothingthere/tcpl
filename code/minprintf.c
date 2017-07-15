/*
使用“剩余参数”实现简化版printf函数
*/

#include <stdarg.h>
#include <stdio.h>

void miniprintf(char *format, ...);

int main(int argc, char const *argv[]) {

  printf("%d\n", 1);
  miniprintf("%d\n", 1);

  printf("%f\n", 1.0);
  miniprintf("%f\n", 1.0);

  printf("%s\n", "claudio");
  miniprintf("%s\n", "claudio");

  return 0;
}

void miniprintf(char *fmt, ...) {
  va_list ap; /*指向各未命名参数*/
  char *p;
  int ival;
  double dval;
  char *sval;
  va_start(ap, fmt);       /*开始让ap指向第一个未命名参数*/
  for (p = fmt; *p; p++) { /*历遍模板字符串fmt*/
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
    case 'd':
      // printf("整数\n");
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for (sval = va_arg(ap, char *); *sval; sval++) {
        putchar(*sval);
      }
      // printf("%s", sval);
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap);
}
