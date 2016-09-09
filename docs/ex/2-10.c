/*重写lower函数，用条件表达式替代if-else语句。*/

#include <stdio.h>
#define MAX_LEN 1000

int get_line(char line[], int lim);
int lower(int c);
void lower_line(char line[]);

int main(int argc, char const *argv[]) {
  int i;
  char line[MAX_LEN];

  while ((i = get_line(line, MAX_LEN)) > 0) {
    lower_line(line);
    printf("%s", line);
  }
  return 0;
}

int lower(int c) { return (c >= 'A' && c <= 'Z') ? (c + ('a' - 'A')) : c; }

void lower_line(char line[]) {
  int i, c;
  for (i = 0; (c = line[i]) != '\0'; i++) {
    line[i] = lower(c);
  }
}

int get_line(char line[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }
  if (c == '\n') {
    line[i] = '\n';
    i++;
  }
  line[i] = '\0';
  return i;
}
