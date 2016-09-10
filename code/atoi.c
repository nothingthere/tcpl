/*简化版的atoi程序*/

#include <stdio.h>
#define MAX_LEN 1000

int get_line(char line[], int lim);
int atoi(char line[]);

int main(int argc, char const *argv[]) {
  int i;
  char line[MAX_LEN];

  while ((i = get_line(line, MAX_LEN)) > 0) {
    printf("%s --> %d\n", line, atoi(line));
  }
  return 0;
}

int atoi(char line[]) {
  int i, n, c;
  for (i = 0, n = 0; c = line[i], c >= '0' && c <= '9'; i++) {
    n = 10 * n + (c - '0');
  }
  return n;
}

int get_line(char line[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }
  // if (c == '\n') {
  //   line[i] = '\n';
  //   i++;
  // }
  line[i] = '\0';
  return i;
}
