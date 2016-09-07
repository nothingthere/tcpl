/*写函数`reverse(s)`，将字符串逆序。*/
#include <stdio.h>
#define MAX_LEN 1000

int get_line(char line[]);     /*读取行，返回长度*/
void str_reverse(char line[]); /*字符串逆序*/
int main(int argc, char const *argv[]) {
  int len; /*当前字符串长度*/
  char line[MAX_LEN];
  while ((len = get_line(line)) > 0) {
    str_reverse(line);
    printf("%s", line);
  }
  return 0;
}

void str_reverse(char line[]) {
  int c, i, j;

  for (j = 0; (c = line[j]) != '\0'; j++) /*求字符串长度*/
    ;
  --j;

  if (line[j] == '\n') { /*排除换行字符*/
    j = j - 1;
  }

  for (i = 0; i < j; i++, j--) {
    c = line[i];
    line[i] = line[j];
    line[j] = c;
  }
}

int get_line(char line[]) {
  int i, c;
  for (i = 0; i < MAX_LEN - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }
  if (c == '\n') {
    line[i] = '\n';
    i++;
  }
  line[i] = '\0';
  return i;
}
