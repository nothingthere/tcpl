/*实现简单版本的C程序define功能（不带参数）。提示：使用getch和ungetch。*/

/*
逐个字符读取，当遇到字符或下划数字线时开始读取“单词”，如果是预处理命令，则开始读取并install，
如果是“单词”且存在于哈希表，则替换。
*/

#include "hash.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 1000 / 10 /*为存储注释和字符串常量，所以很大*/

unsigned hash(char *name);
Nlist *lookup(char *name);
Nlist *install(char *name, char *defn);
void init_hashtable(void);
void destory_hashtable(void);
int uninstall(char *name);
int getch(void);
void ungetch(int);
// int getword(char *word, int lim);
// void putword(char *word);

#define SHARP '#'
#define DQUOTE '"'
#define SQUOTE '\''
#define UNDESCORE '_'
#define SLASH '/'
#define ASTERISK '*'
#define NEWLINE '\n'

#define MY_DEFINE "define"
#define MY_UNDEFINE "undef"

int in_multi_lines_comment = 0;
int in_string = 0;

int main(int argc, char const *argv[]) {
  char name[MAXWORD];
  char defn[MAXWORD];
  char identify[MAXWORD];
  int c;
  char *n;
  char *d;
  char *i;
  Nlist *tmp;
  init_hashtable();
  while ((c = getch()) != EOF) {
    if (isalpha(c) || c == UNDESCORE ||
        c == SHARP) { /*开始读取*单词并查找替换*/
      /*重置指针*/
      n = name;
      d = defn;
      i = identify;
      if (c == SHARP) { /*开始定义注释*/
        // printf("%s\n", "开始定义宏");
        while (isalnum(c = getch())) /*获取定义*/
          *i++ = c;
        *i = '\0';
        ungetch(c);
        while (isblank(c = getch()))
          ;
        ungetch(c);
        // if (strcmp(MY_UNDEFINE, identify) != 0) {

        while (isalnum((c = getch())) || c == UNDESCORE) /*获取定义名*/
          *n++ = c;
        *n = '\0';
        ungetch(c);
        while (isblank(c = getch()))
          ;
        ungetch(c);

        while ((c = getch()) !=
               NEWLINE) /*获取定义,不考虑定义后可能有注释！！！*/
          *d++ = c;
        // 可能是单独的斜线，表示除法
        // if (identify != MY_DEFINE)
        //   ungetch(c);
        //
        // if (identify == MY_UNDEFINE) {
        //   *d++ = '\n';
        //   // *d='\0';
        // }
        *d = '\0';

        // printf("!!!identify=%s, name=%s, defn=%s\n", identify, name, defn);
        if (strcmp(identify, MY_DEFINE) == 0) { /*是预处理宏替换*/
          // printf("install：%s=%s\n", name, defn);
          install(name, defn);
        } else if (strcmp(identify, MY_UNDEFINE) == 0) {
          // printf("uninstall:%s\n", name);
          uninstall(name);
        } else { /*非宏替换*/
          printf("#%s %s %s\n", identify, name, defn);
        }
      } else { /*替换单词*/
        // printf("%s, c=%c\n", "开始替换宏", c);
        *n++ = c;
        while (isalnum(c = getch()) || c == UNDESCORE)
          *n++ = c;
        *n = '\0';
        ungetch(c);
        // printf("name=%s\n", name);
        if ((tmp = lookup(name)) != NULL) {
          printf("%s", tmp->defn);
        } else {
          // printf("%s：%s\n", "没找到替换目标", name);
          printf("%s", name);
        }
      }

    } else if (c == SLASH) { /*可能是注释*/
      c = getch();
      if (c == ASTERISK) { /*多行注释*/
        if (!in_multi_lines_comment) {
          putchar(SLASH);
          putchar(ASTERISK);
          in_multi_lines_comment = 1;
        }
        while ((c = getch()) != ASTERISK)
          putchar(c);
        putchar(ASTERISK);
        c = getch();
        if (c == SLASH) { /*多行注释结束*/
          putchar(c);
          in_multi_lines_comment = 0;
        } else { /*多行注释内有单个星号*/
          // putchar(c);
          ungetch(c);
          ungetch(ASTERISK);
          ungetch(SLASH);
        }

      } else if (c == SLASH) { /*单行注释*/
        putchar(SLASH);
        putchar(SLASH);
        while ((c = getch()) != '\n')
          putchar(c);
        putchar('\n');
      } else { /*非注释*/
        putchar(SLASH);
        putchar(c);
      }
    } else if (c == SQUOTE) { /*排除双引号字符常量*/
      putchar(c);
      while (!((c = getch()) == SQUOTE || c == '\\'))
        putchar(c);
      putchar(c);
      if (c == '\\') {
        putchar(getch());
        while ((c = getch()) != SQUOTE)
          putchar(c);
        putchar(SQUOTE);
      }
    } else if (c == DQUOTE) { /*可能是字符串常量*/
      // printf("%s", "!!!!!SD");
      if (!in_string)
        putchar(DQUOTE);
      while (!((c = getch()) == DQUOTE || c == '\\'))
        putchar(c);
      putchar(c);
      if (c == '\\') { /*跳过转义字符*/
        in_string = 1;
        putchar(getch());
        ungetch(DQUOTE);
      } else {
        in_string = 0;
      }

    } else { /*默认情况*/
      putchar(c);
    }
  }
  destory_hashtable();
  return 0;
}

#define BUFFSIZE 3
char buff[BUFFSIZE];
char *buffp = buff;

int getch(void) { return buffp > buff ? *--buffp : getchar(); }

void ungetch(int c) {
  if (buffp < buff + BUFFSIZE)
    *buffp++ = c;
  else
    printf("buff已满\n");
}
