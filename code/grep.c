/*类似于UNIX中的grep命令*/

#include <stdio.h>
#define MAX_LINE 1000 /*字符串中可包含的最多字符数*/

int get_line(char line[], int lim);
int strindex(char source[], char sarchfor[]);
char pattern[] = "horses";

int main(int argc, char const *argv[]) {
  char line[MAX_LINE];
  int found = 0;
  while ((get_line(line, MAX_LINE)) > 0) {
    if (strindex(line, pattern) >= 0) {
      printf("%s", line);
    }
    // printf("%s\n", line);
  }
  return found;
}

int strindex(char source[], char searchfor[]) {
  int i, j, k;

  for (i = 0; source[i] != '\0'; i++) {
    for (j = i, k = 0; searchfor[k] != '\0' && source[j] == searchfor[k];
         k++, j++)
      ;
    if (k > 0 && searchfor[k] == '\0') {
      return i;
    }
  }
  return -1;
}

int get_line(char line[], int lim) {
  int i, c;
  i = 0;
  while (--lim && (c = getchar()) != EOF && c != '\n') {
    line[i++] = c;
  }
  if (c == '\n') {
    line[i++] = c;
  }
  line[i] = '\0';
  return i;
}
