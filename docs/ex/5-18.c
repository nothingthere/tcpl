/*使dcl程序能从输入错误中恢复过来。

尝试每行单独处理
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

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
char *linep = line;

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
    printf("%s: %s %s\n", name, out, datatype);
    // printf("token:%s\n\n", datatype);
  }
  return 0;
}

void dcl(void) {
  int ns;
  for (ns = 0; gettoken() == '*';)
    ns++;
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
    ungetch(c);
    *p = '\0';
    tokentype = NAME;
  } else {
    tokentype = c;
  }
  return tokentype;
}

#define BUFFSIZE 10
char buff[BUFFSIZE];
char *buffp = buff;

int getch(void) {
  int c = buffp > buff ? *--buffp : *linep++;
  return c;
}
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
