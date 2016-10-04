/*
添加-f参数，排序时忽略大小写。
*/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 20000
#define MAXLEN 1000
#define CAST_COMP (int (*)(const void *, const void *))

int getlines(char *lineptr[], int maxlines);
int get_line(char *line, int lim);
void qsortlines(void *v[], int left, int right, int reverse,
                int (*comp)(const void *, const void *));
void swap(void *v[], int i, int j);
int numcmp(char *s, char *t);
int strcmp_ignore_case(char *s, char *t);
void writelines(char *lineptr[], int nlines);
void freelines(void *v[], int nlines);

int main(int argc, char const *argv[]) {
  // 获得参数
  int c;
  int numeric, reverse, ignore_case;
  numeric = reverse = ignore_case = 0;
  while (--argc && (*++argv)[0] == '-') {
    while ((c = *++argv[0]) != '\0') {
      switch (c) {
      case 'n':
        numeric = 1;
        break;
      case 'r':
        reverse = 1;
        break;
      case 'f':
        ignore_case = 1;
        break;
      default:
        printf("不支持参数：%c\n", c);
        break;
      }
    }
  }
  // printf("reverse=%d ignore_case=%d numeric=%d\n", reverse, ignore_case,
  //        numeric);
  // 通过参数实现排序并输出
  char *lineptr[MAXLINES];
  int nlines;
  int (*comp)(const void *, const void *);
  // comp = (int (*)(const void *, const void *))(
  //   if(numeric)
  //     return numcmp;
  // )
  if (numeric)
    comp = CAST_COMP numcmp;
  else if (ignore_case)
    comp = CAST_COMP strcmp_ignore_case;
  else
    comp = CAST_COMP strcmp;

  // comp = CAST_COMP {
  //   if (numeric == 1)
  //     numcmp;
  //   else if (ignore_case == 1)
  //     strcmp_ignore_case;
  //   else
  //     strcmp;
  // };

  if ((nlines = getlines(lineptr, MAXLINES)) > 0) {
    qsortlines((void **)lineptr, 0, nlines - 1, reverse, comp);
    writelines(lineptr, nlines);
    freelines((void **)lineptr, nlines);
  } else if (nlines != 0) {
    printf("超过行数上限%d\n", MAXLINES);
    freelines((void **)lineptr, nlines);
  } else {
    printf("无文本\n");
  }
  return 0;
}

int getlines(char *lineptr[], int maxlines) {
  char line[MAXLEN];
  int len;
  int nlines = 0;
  char *p;
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

void qsortlines(void *v[], int left, int right, int reverse,
                int (*comp)(const void *, const void *)) {
  int i, last, cmp_result;

  if (left >= right)
    return;

  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    cmp_result = (*comp)(v[i], v[left]);
    if (reverse)
      cmp_result = -cmp_result;
    if (cmp_result < 0)
      swap(v, i, ++last);
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

int strcmp_ignore_case(char *s, char *t) {
  // printf("ignore_case\n");
  char tmp_s, tmp_t;
  while (*s != '\0' && *t != '\0') {
    tmp_s = tolower(*s), tmp_t = tolower(*t);
    if (tmp_s != tmp_t)
      return tmp_s - tmp_t;
    else
      s++, t++;
  }
  if (*s == '\0' && *t == '\0')
    return 0;
  else
    return tolower(*s) - tolower(*t);
}

int numcmp(char *s, char *t) {
  double val1 = atof(s);
  double val2 = atof(t);
  if (val1 < val2)
    return -1;
  else if (val1 > val2)
    return 1;
  else
    return 0;
}

void writelines(char *lineptr[], int nlines) {
  while (nlines--)
    printf("%s", *lineptr++);
}

void freelines(void *v[], int nlines) {
  while (nlines--)
    free(*v++);
}
