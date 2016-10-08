/*
扩展dcl程序，使其能处理函数参数，和类似于const的声明。

处理空格：gettoken函数中，当c=='('时跳过空格。
const等声明：在dcl中与获取`*`同时处理
函数参数：也相当于一个dcl，在dirdcl中当tokentype=='('时处理？？？
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

#define EAT_BLANK(c)                                                           \
  while ((c = getch()) == ' ' || c == '\t')                                    \
    ;

// 颜色宏
#define COLOR_RESET "\033[0m"
#define BOLD "\033[1m"
#define BLACK "\033[30;1m"
#define RED "\033[31;1m"
#define GREEN "\033[32;1m"
#define YELLOW "\033[33;1m"
#define BLUE "\033[34;1m"
#define MAGENTA "\033[35;1m"
#define CYAN "\033[36;1m"
#define WHITE "\033[37;1m"

enum { NAME, PARENS, BRACKETS };

int get_line(char *line, int lim);
int gettoken(void);
int getch(void);
void ungetch(int c);
void dcl(void);
void dirdcl(void);

#define MAXTOKEN 100
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char token[MAXTOKEN];
int tokentype;
char out[1000];
char line[MAXLEN];
char *linep;

int main(int argc, char const *argv[]) {
  while ((get_line(line, MAXLEN)) > 0) {
    linep = line;
    // printf("linep:%s", linep);
    gettoken();
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if (tokentype != '\n')
      printf("语法错误\n");
    printf(BLUE "%s" COLOR_RESET ":" YELLOW " %s" COLOR_RESET GREEN
                " %s" COLOR_RESET "\n",
           name, out, datatype);
    // printf("token:%s\n\n", datatype);
  }
  return 0;
}

void dcl(void) {
  int ns = 0;
  int prev;                                          /*上一个datatype*/
  while ((gettoken()) == NAME || tokentype == '*') { /*吃掉了下一个token*/
    if (tokentype == NAME) { /*如果是const等附加声明*/
      if (prev == '*') /*如果上一个datatype是指针*，则不再继续*/
        break;
      strcat(datatype, " ");
      strcat(datatype, token);
    } else {
      ns++;
    }
    prev = tokentype;
  }
  // 处理*指针声明

  dirdcl();
  while (ns--)
    strcat(out, " pointer to");
}

void dirdcl(void) {
  int type;
  if (tokentype == '(') {
    dcl();
    if (tokentype != ')')
      printf("error:expect')'\n");
  } else if (tokentype == NAME) {
    strcpy(name, token);
  } else {
    printf("error!?");
  }

  while ((type = gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}

int gettoken(void) {
  int c;
  char *p = token;
  EAT_BLANK(c);
  if (c == '(') {
    EAT_BLANK(c);
    if (c == ')') {
      strcpy(token, "()");
      tokentype = PARENS;
    } else {
      ungetch(c);
      tokentype = '(';
    }
  } else if (c == '[') {
    for (*p++ = c; (*p++ = getch()) != ']';)
      ;
    *p = '\0';
    tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch());)
      *p++ = c;
    ungetch(c);
    *p = '\0';
    tokentype = NAME;
  } else {
    tokentype = c;
  }
  return tokentype;
}

#define BUFFSIZE 1
char buff[BUFFSIZE];
char *buffp = buff;

int getch(void) { return buffp > buff ? *--buffp : *linep++; }

void ungetch(int c) {
  if (buffp < BUFFSIZE + buff)
    *buffp++ = c;
  else
    printf("buff已满\n");
}

int get_line(char *line, int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    *line++ = c;
  if (c == '\n') {
    *line++ = c;
    i++;
  }

  *line = '\0';
  return i;
}
