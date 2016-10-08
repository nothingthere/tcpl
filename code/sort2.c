/*
使用函数指针实现排序
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 200000
#define MAXLEN 1000

int getlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
int numcmp(const char *, const char *);
void qsortlines(void *lineptr[], int left, int right,
                int (*comp)(const void *, const void *));
void freelines(char *lineptr[], int nlines);

int main(int argc, char const *argv[]) {
  int nlines;      /*总共获取的行数*/
  int numeric = 0; /*是否使用数字排序*/
  char *lineptr[MAXLINES];
  // 确定参数
  if (argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;
  // 排序并打印结果
  if ((nlines = getlines(lineptr, MAXLINES)) > 0) {
    qsortlines(
        (void **)lineptr, 0, nlines - 1,
        (int (*)(const void *, const void *))(numeric ? numcmp : strcmp));
    writelines(lineptr, nlines);
    freelines(lineptr, nlines);
  } else if (nlines != 0) {
    printf("超出行数上限%d：%d\n", MAXLINES, nlines);
    freelines(lineptr, MAXLINES);
    return 1;
  } else {
    printf("无文本\n");
    return 1;
  }
}

void qsortlines(void *v[], int left, int right,
                int (*comp)(const void *, const void *)) {
  int i, last;
  void swap(void *[], int i, int j);
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if ((*comp)(v[i], v[left]) < 0)
      swap(v, i, ++last);
  }
  swap(v, left, last);

  qsortlines(v, left, last - 1, comp);
  qsortlines(v, last + 1, right, comp);
}

#include <stdlib.h>
int numcmp(const char *s, const char *t) {
  double val1 = atof(s);
  double val2 = atof(t);
  if (val1 < val2)
    return -1;
  else if (val1 > val2)
    return 1;
  else
    return 1;
}

void swap(void *v[], int i, int j) {
  void *tmp;
  tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
}

int get_line(char *line, int lim);
int getlines(char *lineptr[], int maxlines) {
  int len;
  char line[MAXLEN];
  char *p;
  int nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0) {
    if (nlines < maxlines &&
        (p = (char *)malloc(sizeof(char) * (len + 1))) != NULL) {
      strcpy(p, line);
      lineptr[nlines++] = p;
    } else {
      return -1;
    }
  }
  return nlines;
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

void freelines(char *lineptr[], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    free(*lineptr++);
}

void writelines(char *lineptr[], int nlines) {
  while (nlines--)
    printf("%s", *lineptr++);
}
