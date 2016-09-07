/*打印每行，去除行末空格和tab，并去除空行。*/
#include <stdio.h>
#define MAX_LEN 1000

int str_len(char str[]);     /*返回字符串长度*/
int get_line(char line[]);   /*读取行，返回长度*/
void tail_trim(char line[]); /*去除行末空格*/

int main(int argc, char const *argv[]) {
  int len; /*当前字符串长度*/
  char line[MAX_LEN];
  while ((len = get_line(line)) > 0) {
    tail_trim(line);
    printf("%s", line);
  }
  return 0;
}

int str_len(char str[]) {
  int i;
  for (i = 0; str[i] != '\0'; i++)
    ;
  return i;
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

void tail_trim(char line[]) {
  int n;
  char c;
  for (n = str_len(line) - 1; n >= 0; n--) {
    c = line[n];
    if (c != ' ' && c != '\t' && c != '\n') {
      break;
    }
  }
  // 如果是空行，n为-1；
  if (0) { /*不是空行*/
    line[n + 1] = '\n';
    line[n + 2] = '\0';
  } else { /*空行*/
    line[n + 1] = '\0';
  }
}
