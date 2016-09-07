/*输出文本时，用`\t`代替tab，`\b`代替后退字符，`\\`代替反斜杠*/

#include <stdio.h>

int main(int argc, char const *argv[]) {
  int c;
  while ((c = getchar()) != EOF) {
    switch (c) {
    case '\b':
      putchar('\\');
      putchar('b');
      break;
    case '\\':
      putchar('\\');
      putchar('\\');
      break;
    case '\t':
      putchar('\\');
      putchar('t');
      break;
    default:
      putchar(c);
      break;
    }
  }
  return 0;
}
