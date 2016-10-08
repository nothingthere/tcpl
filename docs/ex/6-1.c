/*
改进getword函数，使其支持下划线、字符串常量、注释和预处理行。
*/

#include <stdio.h>
// #include <stddef.h>
// size_t a = 1000;
char *kewords[] = {"__dir",    "auto",     "break",    "case",   "char",
                   "const",    "continue", "default",  "define", "extern",
                   "ifndef",   "include",  "return",   "size_t", "sizeof",
                   "unsigned", "void",     "volatile", "while"};
#define KEYSLEN sizeof(kewords) / sizeof(kewords[0])

#define SHARP '#'
#define QUOTE '"'
#define UNDESCORE '_'
#define SLASH '/'

struct key {
  char *word;
  int count;
} keytab[KEYSLEN];

void init_keytab(void) {
  int i;
  for (i = 0; i < KEYSLEN; i++) {
    keytab[i].word = kewords[i];
    keytab[i].count = 0;
  }
}

void train_keytab(char *s) {
  int binsearch(char *word, struct key tab[], int n);
  int n;
  if ((n = binsearch(s, keytab, KEYSLEN)) >= 0) {
    keytab[n].count++;
  }
}

void print_keytab(void) {
  int i;
  for (i = 0; i < KEYSLEN; i++)
    if (keytab[i].count > 0)
      printf("%4d %s\n", keytab[i].count, keytab[i].word);
}

#define MAXLEN 100
int main(int argc, char const *argv[]) {
  // test_getword();
  int getword(char *, int);
  char word[MAXLEN];
  init_keytab();
  //
  while (getword(word, MAXLEN) != EOF)
    // printf("%s\n", word);
    train_keytab(word);
  //
  print_keytab();
  return 0;
}

#include <string.h>

int binsearch(char *word, struct key tab[], int n) {
  int cond;
  int low, mid, high;
  low = 0, high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0) {
      high = mid - 1;
    } else if (cond > 0) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

#include <ctype.h>

int getword(char *word, int lim) {
  int getch(void);
  void ungetch(int);
  int c;
  static int prev; /*使用函数内静态变量，记录上一个字符是否为单引号*/
  while (isblank(c = getch()))
    ;

  if (c != EOF) {
    *word++ = c;
  }
  // 跳过字符串常量
  // 跳过注释
  // 跳过预处理命令

  if (!(isalpha(c) || (c == SHARP) || (c == QUOTE) || (c == UNDESCORE) ||
        (c == SLASH))) {
    *word = '\0';
    prev = c;
    // printf("%d\n", prev);
    return c;
  }

  switch (c) {
  case SHARP:
    *--word = '\0';
    return getword(word, lim);
    break;
  case QUOTE:
    /*
 一个双引号可能到下一个单引号结束："...."
 可能为字符双引号 '"'
    如果上个字符为单引号，则返回此双引号

 字符串常量不能跨行书写

*/
    if (prev == '\'') { /*如果是在单引号之间*/
      *word = c;
      return c;
    } else {
      while (getch() != '"')
        ;
      *--word = '\0';
      return getword(word, lim);
    }

    break;
  case SLASH:
    c = getch();
    // printf("%c\n", c);
    if (c == SLASH) { /*是注释*/
      while (getch() != '\n')
        ;
      *--word = '\0';
      return getword(word, lim);
    } else { /*不是注释*/
      *word = '\0';
      return c;
    }
    break;
  default: /*c为alnum或下划线*/
    for (; --lim; word++) {
      if (!(isalnum(*word = getch()) || *word == UNDESCORE)) {
        ungetch(*word);
        break;
      }
    }
    break;
  }

  *word = '\0';
  return word[0];
}

#define BUFFSIZE 1
char buff[BUFFSIZE];
char *buffp = buff;
int getch(void) { return buffp > buff ? *--buffp : getchar(); }
void ungetch(int c) {
  if (buffp < buff + BUFFSIZE)
    *buffp++ = c;
  else
    printf("buff已满\n");
}
