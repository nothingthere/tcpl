/*打印出最长行数，不管有多长。*/

#include <stdio.h>
#include <stdlib.h>
#define BASE 1

char *get_line(void);
void copy_line(char *from, char *to);
int str_len(char *s);

int main(int argc, char const *argv[]) {
  int len = 0; /*当前字符串长度*/
  int max = 0; /*最长字符串长度*/
  char *longest = malloc(0);
  char *line;
  while ((line = get_line()) && (len = str_len(line)) > 0) {
    if (len > max) {
      longest = realloc(longest, sizeof(char) * (len + 1));
      longest = line;
      // copy_line(longest, line);
      max = len;
    }
  }
  // }
  //
  if (max > 0) {
    printf("%s\n", longest);
  }

  free(line);
  free(longest);

  return 0;
}

char *get_line(void) {

  int chars = 0;
  char *line = (char *)malloc(sizeof(char) * chars);
  // char *line;

  int c, i;
  for (i = 0; (c = getchar()) != EOF && c != '\n'; i++) {
    chars++;
    line = (char *)realloc(line, chars);
    line[i] = c;
  }

  if (c == '\n') {
    chars++;
    line = (char *)realloc(line, chars);
    line[i] = '\n';
    i++;
  }

  chars++;
  line = (char *)realloc(line, chars);
  line[i] = '\0';
  return line;
}

void copy_line(char *from, char *to) {
  int i = 0;
  while ((*(from + i) = *(to + i)) != '\n') {
    i++;
  }
}

int str_len(char *s) {
  int i;
  int c;
  for (i = 0; (c = *(s++)) != '\0'; i++)
    ;
  return i;
}
