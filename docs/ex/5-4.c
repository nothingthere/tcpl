/*定义str_end(s,t)函数，如果字符串t与s字符串末尾相同，返回1，否则返回0。*/

#include <stdio.h>
#include <string.h>

int str_end(char *s, char *t);

int main(int argc, char const *argv[]) {
  char *s = "have";
  char *t1 = "ave";
  char *t2 = "av";
  printf("\"%s\" end in \"%s\"：%s\n", t1, s, str_end(s, t1) ? "YES" : "NO");
  printf("\"%s\" end in \"%s\"：%s\n", t2, s, str_end(s, t2) ? "YES" : "NO");
  return 0;
}

int str_end(char *s, char *t) {
  int len_s = strlen(s);
  int len_t = strlen(t);
  int i = len_t;
  for (s += len_s - 1, t += len_t - 1; i > 0; i--, s--, t--) {
    if (*s != *t)
      return 0;
  }
  return 1;
}
