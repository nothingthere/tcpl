/*
实现程序相互转换字符大写和小写，依据argv[0]（程序名称？）确定转换为大写还是小写。
*/

/*

实现方法，使用cc命令更改执行文件名称
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LOWER "lower"
#define UPPER "upper"

void lower(void);
void upper(void);
void copy(void);
int main(int argc, char const *argv[]) {
  printf("%s\n", argv[0] + 2);
  const char *type = argv[0] + 2;
  if (strcmp(type, LOWER) == 0) {
    // printf("tolower\n");
    lower();
  } else if (strcmp(type, UPPER) == 0) {
    upper();
  } else {
    copy();
  }
  return 0;
}

void lower(void) {
  int c;
  while ((c = getchar()) != EOF) {
    if (isalpha(c))
      putchar(tolower(c));
    else
      putchar(c);
  }
}

void upper(void) {
  int c;
  while ((c = getchar()) != EOF) {
    if (isalpha(c))
      putchar(toupper(c));
    else
      putchar(c);
  }
}

void copy(void) {
  int c;
  while ((c = getchar()) != EOF)
    putchar(c);
}
