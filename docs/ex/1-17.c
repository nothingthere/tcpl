/*打印出长度大于字符个数大于80的行。*/

#include <stdio.h>
#define MAX_LEN 1000
#define LIMIT 81 /*至少80个字符，留i一个给\0*/

int get_line(char *);

int main(int argc, char const *argv[]) {

  int len;
  char line[MAX_LEN];

  while ((len = get_line(line)) > 0) {
    // printf("%d\n", len);
    if (len > LIMIT) {
      printf("%s", line);
    }
  }

  return 0;
}

int get_line(char *line) {
  int i, c;
  for (i = 0; i < MAX_LEN - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }

  if (c == '\n') {
    line[i] = '\n';
    i++;
  }

  line[i] = '\0';

  // printf("%d\n", i);
  return i;
}
