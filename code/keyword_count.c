/*
keyword_count.c：计算C源文件关键字数量
*/

struct key {
  char *word;
  int count;
} static keytab[] = {{"auto", 0},    {"break", 0},    {"case", 0},
                     {"char", 0},    {"const", 0},    {"continue", 0},
                     {"default", 0}, {"int", 0},      {"unsigned", 0},
                     {"void", 0},    {"volatile", 0}, {"while", 0}};

#define NKEYS sizeof(keytab) / sizeof(keytab[0])

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 100

int getword(char *, int lim);
int binsearch(char *, struct key *, int);

int main(int argc, char const *argv[]) {
  int n;
  char word[MAXWORD];
  // printf("%lu\n", NKEYS);
  // 读取并计数
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]))
      if ((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;
    // printf("%s\n", word);
  }

  // 打印结果
  for (n = 0; n < NKEYS; n++)
    if (keytab[n].count > 0)
      printf("%4d %s\n", keytab[n].count, keytab[n].word);

  return 0;
}

int binsearch(char *word, struct key table[], int n) {
  int cond;
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, table[mid].word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int getword(char *word, int lim) {
  int getch(void);
  void ungetch(int);
  // char *w = word;
  int c;
  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c != EOF) {
    *word++ = c;
  }
  if (!isalpha(c)) { /*可能返回EOF*/
    *word = '\0';
    return c;
  }
  for (; --lim > 0; word++) {
    if (!isalnum(*word = getch())) {
      ungetch(*word);
      break;
    }
  }

  *word = '\0';
  return word[0];
}

#define BUFFSIZE 1
char buff[BUFFSIZE];
char *buffp = buff;

int getch(void) { return buffp > buff ? *--buffp : getchar(); }

void ungetch(int c) {
  if (buffp < buff + BUFFSIZE) {
    *buffp++ = c;
  } else {
    printf("buff已满\n");
  }
}
