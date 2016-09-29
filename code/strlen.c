/*str_len：返回字符串长度*/

#include <stddef.h>
#include <stdio.h>
int str_len(char *s) {
  int n;
  for (n = 0; *s != '\0'; s++)
    n++;
  return n;
}

ptrdiff_t str_len2(char *s) {
  char *p = s;
  while (*p != '\0')
    p++;
  return p - s;
}

int main(int argc, char const *argv[]) {
  printf("%d\n", str_len("123"));
  printf("%lu\n", str_len2("123"));
  return 0;
}
