/*
用指针代替数组下标重写C语言关键字统计程序
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct key {
  char *word;
  int count;
} keytab[] = {{"auto", 0},     {"break", 0},    {"case", 0},     {"char", 0},
              {"const", 0},    {"continue", 0}, {"default", 0},  {"define", 0},
              {"include", 0},  {"int", 0},      {"size_t", 0},   {"sizeof", 0},
              {"unsigned", 0}, {"void", 0},     {"volatile", 0}, {"while", 0}};

typedef struct key Key;
typedef struct key *Keyptr;

#define NKEYS sizeof(keytab) / sizeof(keytab[0])
#define MAXWORD 100

Keyptr binsearch(char *, Keyptr, int);
int getword(char *, int);

int main(int argc, char const *argv[]) {
  char word[MAXWORD];
  struct key *pk;
  // 读入并统计
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]))
      if ((pk = binsearch(word, keytab, NKEYS)) != NULL)
        pk->count++;
  }

  // 打印结果
  for (pk = keytab; pk < keytab + NKEYS; pk++)
    if (pk->count > 0)
      printf("%4d %s\n", pk->count, pk->word);

  return 0;
}

Keyptr binsearch(char *word, Keyptr tab, int n) {
  Keyptr low = tab;
  Keyptr high = tab + n - 1;
  Keyptr mid;
  int cond;
  while (low <= high) {
    mid = low + (high - low) / 2;
    if ((cond = strcmp(word, mid->word)) < 0)
      high = mid - 1;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return NULL;
}

int getch(void);
void ungetch(int);

#define SHARP '#'
#define QUOTE '"'
#define SLASH '/'
#define UNDERSCORE '_'
#define ASTERISK '*'

int getword(char *word, int lim) {
  int c;
  static int prev;
  while (isblank(c = getch()))
    ;
  if (c != EOF) {
    *word++ = c;
  }
  if (!(isalpha(c) || c == SHARP || c == QUOTE || c == SLASH ||
        c == UNDERSCORE)) {
    *word = '\0';
    prev = c;
    return c;
  }

  switch (c) {
  case SHARP:
    *--word = '\0';
    return getword(word, lim);
    break;
  case QUOTE:
    if (prev == '\'') {
      *--word = '\0';
      return getword(word, lim);
    } else {
      while (getch() != QUOTE)
        ;
      *--word = '\0';
      return getword(word, lim);
    }
    break;
  case SLASH:
    c = getch();
    if (c == SLASH) { /*单行注释*/
      while (getch() != '\n')
        ;
      *--word = '\0';
      return getword(word, lim);
    } else if (c == ASTERISK) { /*多行注释*/
      while (getch() != ASTERISK)
        ;
      c = getch();
      if (c != SLASH) {
        ungetch(SLASH);
        ungetch(ASTERISK);
        ungetch(c);
      }
      *--word = '\0';
      return getword(word, lim);
    } else { /*非注释*/
      ungetch(c);
      *word = '\0';
      return word[0];
    }
    break;
  default: /*为字母或下划线*/
    for (; --lim > 0; word++) {
      if (!(isalnum(*word = getch()) || *word == UNDERSCORE)) {
        ungetch(*word);
        break;
      }
    }
    break;
  }
  *word = '\0';
  return word[0];
}

#define BUFFSIZE 3
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
