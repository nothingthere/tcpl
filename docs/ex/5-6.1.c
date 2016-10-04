/*指针版getline*/

#include <stdio.h>
#define SIZE 1000

int get_line(char *s, int lim);

int main(int argc, char const *argv[]) {
  char line[SIZE];
  while ((get_line(line, SIZE)) > 0) {
    printf("%s", line);
  }
  return 0;
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
