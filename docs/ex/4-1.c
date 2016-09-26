/*重新定义strindex(s, t)，也是返回字符串t在s中的位置，如果不包含，返回-1。
不同的是，从s的右边开始寻找。*/

/*
解决方案：
    1.先求两个字符串的长度，在从右边开始。

    2. 先反转两个字符串，求得索引，如果>=0,则结果为
     s_len - position - 1
       缺点，改变了原有字符串，如果要反转回去，需对两个字符串历遍两次。
       方案1,只需历遍1次。
*/

#include <stdio.h>
#include <string.h>
#define MAX_LINE 1000 /*字符最长字符数*/

int get_line(char line[], int lim);
int str_index(char source[], char pattern[]);

int main(int argc, char const *argv[]) {
  char line[MAX_LINE];
  char pattern[] = "ould";
  int pos;
  while (get_line(line, MAX_LINE) > 0) {
    pos = str_index(line, pattern);
    if (pos >= 0) {
      printf("@%d： %s\n", pos, line);
    }
  }
  // printf("%s\n", line);

  return 0;
}

int str_index(char source[], char pattern[]) {
  int source_len = strlen(source);
  int pattern_len = strlen(pattern);
  int i, j, k;
  for (i = source_len - 1; i >= pattern_len - 1; i--) {
    for (j = i, k = pattern_len - 1; k >= 0 && pattern[k] == source[j];
         j--, k--)
      ;
    if (k == -1) {
      return j;
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
