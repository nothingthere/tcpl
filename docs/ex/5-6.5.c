/*指针版strindex*/

#include <stdio.h>

int str_index(char *s, char *t);
int strindex(char *s, char *t);

int main(int argc, char const *argv[]) {
  char s[] = "i have a dream!";
  char t[] = "have";
  char t2[] = "";

  printf("\"%s\" in \"%s\" @：%d\n", t, s, str_index(s, t));
  printf("\"%s\" in \"%s\" @：%d\n", t2, s, str_index(s, t2));

  return 0;
}

int strindex(char s[], char t[]) {
  int i, j, k;
  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      return i;
  }
  return -1;
}

int str_index(char *s, char *t) {
  int i;
  char *tmp_t;
  char *tmp_s;
  for (i = 0, tmp_t = t, tmp_s = s; *s != '\0'; i++, t = tmp_t, s = ++tmp_s) {
    while (*t != '\0' && *t == *s) {
      /*不使用*t++ == *s++的原因为，如果不等还是会自增*/
      t++, s++;
    }
    if (t > tmp_t && *t == '\0') { /*t > tmp_t保证t所指向的字符串不为空*/
      return i;
    }
  }
  return -1;
}
