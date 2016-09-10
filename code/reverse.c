#include <stdio.h>
#include <string.h>

void reverse(char line[]);
int main(int argc, char const *argv[]) {
  char line[] = "i have a dream";
  printf("原字符串：%s\n", line);
  reverse(line);
  printf("反转后：  %s\n", line);
  return 0;
}

void reverse(char line[]) {
  int i, j, tmp;
  const int len = strlen(line);
  for (i = 0, j = len - 1; i < j; i++, j--) {
    tmp = line[i], line[i] = line[j], line[j] = tmp;
  }
}
