/*实现tail程序，打印输入内容的后n行，n默认值为10。如打印最后n行。不管输入行数和n如何怪异，程序都能运行。
合理分配内存，存储每行文本时需同sort程序一样使用指针数组，而非固定长度的二维数组。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 40000
#define MAXLEN 1000

int lines_to_shown = 10;
void tail(char *lines[], int nlines, int n);
int getlines(char *lines[], int lim);
void freelines(char *lines[], int nlines);

int main(int argc, char const *argv[]) {
  char *lines[MAXLINES];
  int nlines;
  // 解析参数，获取需打印的行数
  if (argc == 2) {
    // printf("%d\n", atoi("12.2"));
    lines_to_shown = atoi(++argv[1]);
  }
  // 获取文本并打印
  if ((nlines = getlines(lines, MAXLINES)) > 0) {
    tail(lines, nlines, lines_to_shown);
    // printf("行数：%d\n", nlines);
    freelines(lines, nlines);
    return 0;
  } else {
    if (nlines == 0) {
      printf("无文本\n");
    } else {
      freelines(lines, MAXLINES);
      printf("函数超过上限：%d\n", MAXLINES);
    }
    return 1;
  }
}

void tail(char *lines[], int nlines, int n) {
  int i;
  if (n > nlines) {
    n = nlines;
  }
  lines += nlines;
  lines -= n;
  for (i = 0; i < n; i++) {
    printf("%s", *lines++);
  }
}

int get_line(char *line, int lim);
int getlines(char *lines[], int maxlines) {
  int nlines = 0;
  int len;
  char *p;
  char line[MAXLEN];
  while ((len = get_line(line, MAXLEN)) > 0) {
    // nlines++;
    // printf("%s", line);
    if (nlines < maxlines &&
        (p = (char *)malloc(sizeof(char) * (len + 1))) != NULL) {
      strcpy(p, line);
      lines[nlines++] = p;
    } else {
      return -1;
    }
  }
  // printf("%d\n", nlines);
  return nlines;
}

void freelines(char *lines[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    free(*lines++);
}

int get_line(char *line, int lim) {
  int i, c;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    *line++ = c;

  if (c == '\n') {
    *line++ = c;
    i++;
  }

  *line = '\0';
  return i;
}
