/*
修改第一章的entab和detab程序，使其接收一串tab stop作为参数。
如果未提供参数，使用默认值。
*/

#include <stdio.h>
#include <stdlib.h>

#define BLANK '@'
#define TAB '#'
#define isblank(c) ((c) == BLANK)
#define istab(c) ((c) == TAB)
#define MAXLEN 1000

int Blanks = 4; /*一个tab被多少个空格代替*/

void handle_entab(char *s, int n);
void handle_detab(char *s, int n);
int get_line(char *s, int lim);
void panic(char *msg); /*报错函数*/
/*
程序可接受2个参数
第一个为-e(entab)/-d(detab)
第二个为替换tab的空格数/多少个空格替换一个tab。数值
*/

int main(int argc, char const *argv[]) {
  int detab, entab;
  detab = entab = 0;
  int blanks;
  const char *argv1, *argv2;
  char line[MAXLEN];
  // 解析第一个参数：确定操作
  if (argc < 2) /*没有参数*/
    panic("用法：至少提供一个参数");
  // 解析第一个参数
  argv1 = argv[1];
  // printf("argv1:%s\n", argv1);
  if (argv1[0] != '-') {
    panic("第一个参数应为：-e/-d");
  } else {
    if (argv1[1] == 'e')
      entab = 1;
    else if (argv1[1] == 'd')
      detab = 1;
    else
      panic("不支持此操作！");
  }
  // 解析第二个参数，获取blanks
  argv2 = argv[2];
  if (argv2) {
    // printf("argv2:%s\n", argv2);
    blanks = (int)atof(argv2);
    // printf("blanks=%d\n", blanks);
    if (blanks > 0)
      Blanks = blanks;
    else
      panic("不支持此tab数量");
  }
  // printf("操作：%s Blanks=%d\n", detab ? "detab" : "entab", Blanks);

  // 进行操作
  while (get_line(line, MAXLEN) > 0) {
    if (entab) {
      handle_entab(line, Blanks);
      // printf("%s", line);
    }
    if (detab) {
      handle_detab(line, Blanks);
      // printf("%s", line);
    }
  }
  return 0;
}

void panic(char *msg) {
  printf("%s\n", msg);
  exit(1);
}

void handle_detab(char *line, int n) {
  int c, i;
  while ((c = *line) != '\0') {
    if (istab(c)) {
      for (i = 0; i < n; i++)
        putchar(BLANK);
    } else {
      putchar(c);
    }
    line++;
  }
}
void handle_entab(char *line, int n) {
  int c, i;
  int tmp = 0;
  while ((c = *line) != '\0') {
    if (isblank(c)) {
      tmp++;
    } else {
      for (i = 0; i < tmp / Blanks; i++)
        putchar(TAB);
      for (i = 0; i < tmp % Blanks; i++)
        putchar(BLANK);
      tmp = 0;
      putchar(c);
    }
    line++;
  }
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
