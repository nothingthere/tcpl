/*
添加-d参数，只比较字母、数字和空格。可兼容-f和-r参数
*/

#include <ctype.h> /*tolower*/
#include <stdio.h>
#include <stdlib.h> /*mallo free atof*/
#include <string.h> /*strcmp*/

#define MAXLEN 1000
#define MAXLINES 20000
#define CAST_COMP (int (*)(const void *, const void *))
#define IS_PURE_CHAR(c) ((isalnum(c) || isspace(c)))

int getlines(char *lineptr[], int maxlines);
void qsortlines(void *v[], int left, int right, int reverse,
                int (*comp)(const void *, const void *));
int numcmp(const char *, const char *);
int strcmp_ignore_case(const char *, const char *);
int strcmp_ignore_case_pure(const char *, const char *);
int strcmp_pure(const char *, const char *);

void writelines(char *lineptr[], int nlines);
void freelines(void *v[], int nlines);

int main(int argc, char const *argv[]) {
  // 确定参数
  //  -n -f -r -d
  int c;
  int numeric, ignore_case, reverse, pure;
  numeric = ignore_case = reverse = pure = 0;
  while (--argc && (*++argv)[0] == '-') {
    while ((c = *++argv[0]) != '\0') {
      switch (c) {
      case 'n':
        numeric = 1;
        break;
      case 'f':
        ignore_case = 1;
        break;
      case 'r':
        reverse = 1;
        break;
      case 'd':
        pure = 1;
        break;
      default:
        printf("不支持参数：%c\n", c);
        break;
      }
    }
  }
  printf("numeric=%d, ignore_case=%d, reverse=%d, pure=%d\n", numeric,
         ignore_case, reverse, pure);
  // 根据参数读取->排序->打印
  char *lineptr[MAXLINES];
  int nlines;
  int (*comp)(const void *, const void *);
  // 确认比较函数
  if (ignore_case && pure)
    comp = CAST_COMP strcmp_ignore_case_pure;
  else if (ignore_case)
    comp = CAST_COMP strcmp_ignore_case;
  else if (pure)
    comp = CAST_COMP strcmp_pure;
  else if (numeric)
    comp = CAST_COMP numcmp;
  else
    comp = CAST_COMP strcmp;
  //
  if ((nlines = getlines(lineptr, MAXLINES)) > 0) {
    qsortlines((void **)lineptr, 0, nlines - 1, reverse, comp);
    writelines(lineptr, nlines);
    freelines((void **)lineptr, nlines);
  } else if (nlines != 0) {
    printf("行数超过上限\n");
    freelines((void **)lineptr, MAXLINES);
  } else {
    printf("无文本\n");
  }
  return 0;
}

int getlines(char *lineptr[], int maxlines) {
  int get_line(char *, int);
  int nlines, len;
  char line[MAXLEN];
  char *p;
  nlines = 0;
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

  int i, last;
  void swap(void *v[], int i, int j);
  int comp_result;

  if (left >= right)
    return;

  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    comp_result = (*comp)(v[i], v[left]);
    if (reverse)
      comp_result = -comp_result;

    if (comp_result < 0)
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

void writelines(char *lineptr[], int nlines) {
  while (nlines--)
    printf("%s", *lineptr++);
}

void freelines(void *v[], int nlines) {
  while (nlines--)
    free(*v++);
}

int numcmp(const char *s, const char *t) {
  double val1 = atof(s);
  double val2 = atof(t);
  if (val1 < val2)
    return -1;
  else if (val1 > val2)
    return 1;
  else
    return 0;
}

int strcmp_ignore_case(const char *s, const char *t) {
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

int strcmp_ignore_case_pure(const char *s, const char *t) {
  char tmp_s, tmp_t;
  while (*s != '\0' && *t != '\0') {
    if (!IS_PURE_CHAR(*s)) {
      s++;
      continue;
    }

    if (!IS_PURE_CHAR(*t)) {
      t++;
      continue;
    }

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

int strcmp_pure(const char *s, const char *t) {
  while (*s != '\0' && *t != '\0') {
    if (!IS_PURE_CHAR(*s)) {
      s++;
      continue;
    }

    if (!IS_PURE_CHAR(*t)) {
      t++;
      continue;
    }

    if (*s != *t)
      return *s - *t;
    else
      s++, t++;
  }

  if (*s == '\0' && *t == '\0')
    return 0;
  else
    return *s - *t;
}
