
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 颜色宏
#define COLOR_RESET "\033[0m"
#define BLACK "\033[30;1m"
#define GREEN "\033[32;1m"
#define YELLOW "\033[33;1m"
#define BLUE "\033[34;1m"
#define MAGENTA "\033[35;1m"
#define CYAN "\033[36;1m"
#define WHITE "\033[37;1m"

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
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n') {
      if (type == PARENS || type == BRACKETS) {
        strcat(out, token);
      } else if (type == '*') {
        sprintf(temp, "(*%s)", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else
        printf("非法token：%s\n", token);
    }
    printf("%s\n", out);
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
