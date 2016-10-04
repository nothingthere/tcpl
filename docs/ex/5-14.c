/*
修改sort程序，使其支持逆向排序参数-r，确保与能与-n参数一起使用。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 20000
#define MAXLEN 1000

void qsortlines(void *v[], int left, int right, int reverse,
                int (*comp)(const void *, const void *));
int get_line(char *line, int lim);
int getlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void freelines(void *v[], int nlines);
int numcmp(const char *, const char *);

int main(int argc, char const *argv[]) {
  // 确定参数
  int numeric, reverse;
  int c;
  numeric = reverse = 0;

  while (--argc > 0 && (*++argv)[0] == '-') {
    while ((c = *++argv[0]) != '\0') {
      switch (c) {
      case 'n':
        numeric = 1;
        break;
      case 'r':
        reverse = 1;
        break;
      default:
        printf("不支持命令：%c\n", c);
        break;
      }
    }
  }
  // printf("numeric=%d reverse=%d\n", numeric, reverse);
  // 排序并显示结果
  int nlines;
  char *lineptr[MAXLINES];
  if ((nlines = getlines(lineptr, MAXLINES)) > 0) {
    qsortlines(
        (void **)lineptr, 0, nlines - 1, reverse,
        (int (*)(const void *, const void *))(numeric ? numcmp : strcmp));
    writelines(lineptr, nlines);
    freelines((void **)lineptr, nlines);
  } else if (nlines != 0) {
    printf("超过行数上限%d：%d\n", MAXLINES, nlines);
    freelines((void **)lineptr, MAXLINES);
  } else {
    printf("无文本\n");
  }
  return 0;
}

void qsortlines(void *v[], int left, int right, int reverse,
                int (*comp)(const void *, const void *)) {
  int i, last;
  void swap(void *v[], int i, int j);
  int cmp_result;
  if (left >= right)
    return;

  swap(v, left, (left + right) / 2);
  last = left;

  for (i = left + 1; i <= right; i++) {
    cmp_result = (*comp)(v[i], v[left]);
    // printf("cmp_result=%d\n", cmp_result);
    if (reverse)
      cmp_result = -cmp_result;
    if (cmp_result < 0) {
      swap(v, i, ++last);
    }
  }
  swap(v, left, last);

  qsortlines(v, left, last - 1, reverse, comp);
  qsortlines(v, last + 1, right, reverse, comp);
}

void swap(void *v[], int i, int j) {
  void *tmp;
  tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
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

int getlines(char *lineptr[], int maxlines) {
  char line[MAXLEN];
  char *p;
  int len;
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

void writelines(char *lineptr[], int nlines) {
  while (nlines--)
    printf("%s", *lineptr++);
}

void freelines(void *v[], int nlines) {
  while (nlines--)
    free(*v++);
}

int numcmp(const char *s, const char *t) {
  double v1 = atof(s);
  double v2 = atof(t);
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  } else {
    return 0;
  }
}
