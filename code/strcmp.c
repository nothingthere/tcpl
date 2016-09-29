/*strcmp:比较字符串大小*/

#include <stdio.h>

int str_cmp1(char *s, char *t);
int str_cmp2(char *s, char *t);

int main(int argc, char const *argv[]) {
  char *s = "1";
  char *t1 = "2";
  char *t2 = "1";
  printf("%d\n", str_cmp1(s, t1));
  printf("%d\n", str_cmp1(s, t2));

  printf("%d\n", str_cmp2(s, t1));
  printf("%d\n", str_cmp2(s, t2));

  return 0;
}

int str_cmp1(char *s, char *t) {
  int i;
  for (i = 0; s[i] == t[i]; i++) {
    if (s[i] == '\0')
      return 0;
  }
  return s[i] - t[i];
}

int str_cmp2(char *s, char *t) {
  for (; *s == *t; s++, t++) {
    if (*s == '\0')
      return 0;
  }
  return *s - *t;
}
