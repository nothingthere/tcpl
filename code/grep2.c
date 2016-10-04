/*
gerp命令，使用命令行参数
*/

#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

int get_line(char *line, int lim);
int main(int argc, char const *argv[]) {
  char line[MAXLEN];
  int found = 0;

  if (argc != 2) {
    printf("使用方法：提供查找字段，打印含该字段的行\n");
    return 1;
  }

  while (get_line(line, MAXLEN) > 0) {
    if (strstr(line, argv[1]) != NULL) {
      printf("%s", line);
      found++;
    }
  }

  return found;
}

int get_line(char *line, int lim) {
  int i, c;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    *line++ = c;
  }
  if (c == '\n') {
    *line++ = c;
    i++;
  }
  *line = '\0';
  return i;
}
