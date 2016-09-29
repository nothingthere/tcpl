/*定义标准库中的strncpy、strncat和strncmp函数，只操作字符串中最多n个字符，如strncpy(s,t,n)，只从t中复制最多n个字符到s。*/

#include <stdio.h>
#include <string.h>

void str_ncpy(char *s, char *t, int n);
void str_ncat(char *s, char *t, int n);
int str_ncmp(char *s, char *t, int n);

int main(int argc, char const *argv[]) {
  int n = 3;

  char s[100] = "";
  char *t = " dream";
  str_ncpy(s, t, n);
  printf("%s\n", s);

  char s1[100] = "i have a";
  char *t1 = " dream";
  str_ncat(s1, t1, n);
  printf("%s\n", s1);

  char s2[100] = "i have";
  char *t2 = "i hd";
  printf("\"%s\" == \"%s\": %s\n", s2, t2,
         str_ncmp(s2, t2, n) == 0 ? "yes" : "no");

  return 0;
}

void str_ncpy(char *s, char *t, int n) {
  int i;
  for (i = 0; i < n && *t != '\0'; i++) {
    *s++ = *t++;
  }
  // putchar(*s);
  // printf("*s=%d\n", *s);
}

void str_ncat(char *s, char *t, int n) {
  int len = strlen(s);
  int i;
  for (s += len, i = 0; i < n && (*s = *t) != '\0'; i++, s++, t++)
    ;
}
int str_ncmp(char *s, char *t, int n) {
  int i;
  for (i = 1; *s == *t; i++, s++, t++) {
    // printf("*s=%c *t=%c i=%d\n", *s, *t, i);
    if (*s == '\0' || i == n)
      return 0;
  }
  return *s - *t;
}
