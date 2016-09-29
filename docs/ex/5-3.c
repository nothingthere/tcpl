/*使用指针定义str_cat(s,t)函数，将t字符串复制到s末尾。*/

#include <stdio.h>
#include <string.h>

void str_cat(char *s, char *t);
int main(int argc, char const *argv[]) {
  char s[100] = "i";
  str_cat(s, " have a dream!");
  printf("%s\n", s);
  return 0;
}
void str_cat(char *s, char *t) {
  int len = strlen(s);
  for (s += len; (*s = *t) != '\0'; s++, t++)
    ;
}
