/*重写readlines函数，将读取来的各行字符串存储在main函数中声明的一个变量内，而不是使用alloc获取。
整个程序变快多少？
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINES 30000 /*最多读取的行数*/
#define MAXLEN 200
#undef CLK_PER_SEC
#define CLK_PER_SEC 1000

int getlines(char *lineptr[], int maxlines);
void qsortlines(char *lineptr[], int left, int right);
void writelines(char *lineptr[], int nlines);

int getlines2(char lines[][MAXLEN], int maxlines);
void qsortlines2(char lines[][MAXLEN], int left, int right);
void writelines2(char lines[][MAXLEN], int nlines);

void freelines(char *lineptr[], int nlines);
int main(int argc, char const *argv[]) {
  int nlines;
  int start = clock() / CLK_PER_SEC;
  char *lineptr[MAXLINES];
  char lines[MAXLINES][MAXLEN];
  // char lines[MAXLINES][MAXLEN];
  // printf("argc=%d *argv[1]='%c'\n", argc, *argv[1]);
  int V = (argc > 1 && *argv[1] == '2') ? 2 : 1;

  // nlines = getlines(lineptr, MAXLINES);
  switch (V) {
  case 1:
    if ((nlines = getlines(lineptr, MAXLINES)) >= 0) {
      qsortlines(lineptr, 0, nlines - 1);
      writelines(lineptr, nlines);
      freelines(lineptr, nlines);
      printf("\tgetlines: V1。耗时：%ld毫秒\n\n",
             (clock() / CLK_PER_SEC) - start);
      return 0;
    } else {
      freelines(lineptr, MAXLINES);
      printf("超出行数上限\n");
      return 1;
    }
    break;
  default:
    if ((nlines = getlines2(lines, MAXLINES)) >= 0) {
      qsortlines2(lines, 0, nlines - 1);
      writelines2(lines, nlines);
      printf("\tgetlines: V2。耗时：%ld毫秒\n\n",
             (clock() / CLK_PER_SEC) - start);
      return 0;
    } else {
      printf("超出行数上限\n");
      return 1;
    }
    break;
  }
}

int get_line(char *line, int lim);
char *alloc(int n);

int getlines2(char lines[][MAXLEN], int maxlines) {
  printf("\tgetlines: V2\n\n");
  int len;
  // char line[MAXLEN];
  int nlines = 0;
  // char *p;
  while ((len = get_line(lines[nlines], MAXLEN)) > 0) {
    if (nlines >= maxlines) {
      return -1;
    } else {
      lines[nlines++][len - 1] = '\0';
      // line[len - 1] = '\0';
      // strcpy(p, line);
      // lines[nlines++] = p;
    }
  }
  return nlines;
}

int getlines(char *lineptr[], int maxlines) {
  int len;
  char line[MAXLEN];
  int nlines = 0;
  char *p;
  while ((len = get_line(line, MAXLEN)) > 0) {
    if (nlines >= maxlines || (p = (char *)malloc(len)) == NULL) {
      return -1;
    } else {
      line[len - 1] = '\0';
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

void writelines(char *lineptr[], int nlines) {
  while (nlines--)
    printf("%s\n", *lineptr++);
}

void writelines2(char lines[][MAXLEN], int nlines) {
  int i;
  for (i = 0; i < nlines; i++)
    printf("%s\n", lines[i]);
}

void freelines(char *lineptr[], int nlines) {
  while (nlines--)
    free(*lineptr++);
}

void qsortlines(char *lineptr[], int left, int right) {
  int last, i;
  void swap(char *v[], int i, int j);
  if (left >= right)
    return;
  swap(lineptr, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if (strcmp(lineptr[i], lineptr[left]) < 0) {
      ++last;
      if (last != i)
        swap(lineptr, i, last);
    }
  }
  swap(lineptr, left, last);
  qsortlines(lineptr, left, last - 1);
  qsortlines(lineptr, last + 1, right);
}

void swap(char *v[], int i, int j) {
  char *tmp;
  tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
}

void qsortlines2(char lines[][MAXLEN], int left, int right) {
  int last, i;
  void swap2(char v[][MAXLEN], int i, int j);
  if (left >= right)
    return;
  swap2(lines, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if (strcmp(lines[i], lines[left]) < 0) {
      ++last;
      if (last != i)
        swap2(lines, i, last);
    }
  }
  swap2(lines, left, last);
  qsortlines2(lines, left, last - 1);
  qsortlines2(lines, last + 1, right);
}

void swap2(char v[][MAXLEN], int i, int j) {
  char tmp[MAXLEN];
  strcpy(tmp, v[i]);
  strcpy(v[i], v[j]);
  strcpy(v[j], tmp);
  // tmp = v[i];
  // v[i] = v[j];
  // v[j] = tmp;
}

int get_line(char *line, int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    *line++ = c;
  }
  if (c == '\n') {
    *line++ = c;
    i++;
  }
  *line = '\0';
  return i;
}

#define ALLOCSIZE (MAXLINES * MAXLEN)
char allocbuff[ALLOCSIZE];
char *allocp = allocbuff;

char *alloc(int n) {
  if (allocbuff + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else {
    return NULL;
  }
}

// static void afree(char *p) {
//   if (p >= allocbuff && p < allocbuff + ALLOCSIZE) {
//     allocp = p;
//   }
// }
