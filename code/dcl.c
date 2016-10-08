#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 颜色宏
#define COLOR_RESET "\033[0m"
#define BOLD "\033[1m"
#define BLACK_TEXT "\033[30;1m"
#define RED_TEXT "\033[31;1m"
#define GREEN_TEXT "\033[32;1m"
#define YELLOW_TEXT "\033[33;1m"
#define BLUE_TEXT "\033[34;1m"
#define MAGENTA_TEXT "\033[35;1m"
#define CYAN_TEXT "\033[36;1m"
#define WHITE_TEXT "\033[37;1m"

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };
char token[MAXTOKEN];    /*下一个token*/
char name[MAXTOKEN];     /*名字：类型名（int,char..）或变量名字*/
char datatype[MAXTOKEN]; /*int char void...*/
char out[1000];          /*dcl/dirdcl获取token时链接的结果字符串*/
int tokentype;           /*token类型*/

int gettoken(void);
int getch(void);
void ungetch(int c);

void dcl(void);
void dirdcl(void);

int main(int argc, char const *argv[]) {
  while (gettoken() != EOF) {
    strcpy(datatype, token); /*第一个token为名字*/
    out[0] = '\0';           /*清空*/
    dcl();                   /*开始获取*/
    if (tokentype != '\n')
      printf("error：语法错误\n");
    printf("%s:%s %s\n", name, out, datatype);
  }
  return 0;
}

void dcl(void) {
  int ns;
  for (ns = 0; gettoken() == '*';)
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

void dirdcl(void) {
  int type;
  if (tokentype == '(') {
    dcl();
    if (tokentype != ')')
      printf("error：？\n");
  } else if (tokentype == NAME) {
    strcpy(name, token);
  } else
    printf("error: expect (dcl)\n");
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
  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if ((c = getch()) == ')') {
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
    *p = '\0';
    ungetch(c);
    tokentype = NAME;
  } else
    tokentype = c;
  return tokentype;
}

#define BUFFSIZE 1
char buffer[BUFFSIZE];
char *buffp = buffer;

int getch(void) { return buffp > buffer ? *--buffp : getchar(); }
void ungetch(int c) {
  if (buffp < buffer + BUFFSIZE)
    *buffp++ = c;
  else
    printf("buff已满\n");
}
