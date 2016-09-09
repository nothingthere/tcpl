#include <stdio.h>
int get_line(char line[], int lim) {
  int i, c;
  // for (i = 0; i < lim - 1 && (c = getchar() != EOF) && c != '\n'; i++) {
  //   line[i] = c;
  // }
  for (i = 0; i < lim - 1; i++) {
    c = getchar();
    if (c == EOF) {
      break;
    }
    if (c == '\n') {
      break;
    }
  }
  if (c == '\n') {
    line[i] = '\n';
    i++;
  }
  line[i] = '\0';
  return i;
}
