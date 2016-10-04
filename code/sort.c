/*
sort.c
类似于Unix系统的sort工具
*/
#include <stdio.h>
#include <string.h>

#define MAXLINES 50000   /*最多行数*/
char *lineptr[MAXLINES]; /*指向下一行文字符串的指针*/

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsortlines(char *lineptr[], int left, int right);

int main(int argc, char const *argv[]) {
  int nlines; /*总共读取的行数*/
  if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
    qsortlines(lineptr, 0, nlines - 1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("行数超过上限\n");
    return 1;
  }
}

#define MAXLEN 1000 /*每行最大长度*/
int get_line(char *line, int lim);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
  int nlines, len;
  char line[MAXLEN];
  char *p; /*每读取一行，为该行分配内存，再让指针数组中的元素指向此行地址*/
  nlines = 0;
  while ((len = get_line(line, MAXLEN)) > 0) {
    // printf("begin read\n");
    if (nlines >= maxlines || (p = alloc(len)) == NULL) {
      return -1;
    } else {
      line[len - 1] = '\0'; /*去掉末尾的换行符*/
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return nlines;
}

// void writelines(char *lineptr[], int nlines) {
//   int i;
//   for (i = 0; i < nlines; i++)
//     printf("%s\n", lineptr[i]);
// }

void writelines(char *lineptr[], int nlines) {
  while (nlines-- > 0) {
    printf("%s\n", *lineptr++);
  }
}

int get_line(char *line, int lim) {
  int i, c;
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

#define ALLOCSIZE MAXLINES *MAXLEN /*最大可用空间*/
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else {
    return NULL;
  }
}

void afree(char *p) {
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
    allocp = p;
  }
}

void qsortlines(char *v[], int left, int right) {
  int last, i;
  void swap(char *v[], int i, int j);
  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    if (strcmp(v[i], v[left]) <= 0) {
      last++;
      if (i != last)
        swap(v, i, last);
    }
  }
  swap(v, left, last);
  qsortlines(v, left, last - 1);
  qsortlines(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
  char *tmp;
  tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
}
