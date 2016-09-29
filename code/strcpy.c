/*strcpy: 将字符串t复制到s中*/

#include <stdio.h>

void str_cpy1(char *s, char *t);
void str_cpy2(char *s, char *t);

int main(int argc, char const *argv[]) {
  char *name = "the c programming language.";
  char cp1[100];
  char cp2[100];

  str_cpy1(cp1, name);
  printf("%s\n", cp1);
  str_cpy2(cp2, name);
  printf("%s\n", cp2);

  return 0;
}

void str_cpy1(char *s, char *t) { /*下标版本*/
  int i;
  i = 0;
  while ((s[i] = t[i]) != '\0')
    i++;
}

void str_cpy2(char *s, char *t) { /*指针版本*/
  while ((*s = *t) != '\0') {
    s++;
    t++;
  }
}
