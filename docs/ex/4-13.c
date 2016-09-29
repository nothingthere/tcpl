/*用递归定义reverse(s)函数，将字符串s反转。*/
#include <stdio.h>
#include <string.h>

void reverse(char s[]);
static void swap(char s[], int i, int j);

int main(int argc, char const *argv[]) {
  char line[] = "i have a dream!";
  printf("%s\n", line);
  reverse(line);
  printf("%s\n", line);
  return 0;
}

void reverse(char s[]) {
  int len = strlen(s);
  swap(s, 0, len - 1);
}

static void swap(char s[], int i, int j) {
  if (i >= j)
    return;
  int tmp;
  tmp = s[i];
  s[i] = s[j];
  s[j] = tmp;
  swap(s, i + 1, j - 1);
}
