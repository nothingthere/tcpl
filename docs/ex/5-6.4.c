/*指针版reverse*/
#include <stdio.h>
#include <string.h>

void reverse(char *s);
int main(int argc, char const *argv[]) {
  char name[] = "claudio";
  char age[] = "";

  printf("%s -> ", name);
  reverse(name);
  printf("%s\n", name);
  printf("%s -> ", age);
  reverse(age);
  printf("%s\n", age);
  return 0;
}
void reverse(char *s) {
  char *t = s + strlen(s) - 1;
  while (s < t) {
    *s ^= *t ^= *s ^= *t;
    s++, t--;
  }
}
