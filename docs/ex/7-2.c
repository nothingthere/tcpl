/*实现程序合理打印任何输入。至少可根据需求将非图形字符（no-graphic）打印为8/16进制，并换行过长的文本行。*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 20 /*一行最多打印字符数*/
#define NEWLINE '\n'

int oct = 0;
int hex = 0;

int main(int argc, char const *argv[]) {
  int c;
  int i = 0;
  char format[3];

  // 确定参数
  while (--argc > 0 && *(++argv)[0] == '-') {
    while ((c = *(++argv[0])) != '\0')
      switch (tolower(c)) {
      case 'x':
        // oct = 1;
        strcpy(format, "%o");
        break;
      case 'h':
        // hex = 1;
        strcpy(format, "%x");
        break;
      default:
        strcpy(format, "%c");
        break;
      }
  }
  // printf("oct=%d, hex=%d,format=%s\n", oct, hex, format);
  // 打印
  while ((c = getchar()) != EOF) {
    i++;
    if (isblank(c) && i >= MAXLEN) {
      putchar(NEWLINE);
      i = 0;
    } else if (isgraph(c)) {
      putchar(c);
    } else {
      // putchar(c);
      printf(format, c);
    }
  }
  putchar(NEWLINE);
  return 0;
}
