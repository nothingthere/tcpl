/*
简化版grep命令
支持：-x 显示不匹配行
    -n 在行首打印行数
*/

#include <stdio.h>
#include <string.h>

#define MAXLEN 1000
int get_line(char *s, int lim);

int main(int argc, char const *argv[]) {
  long lineno = 0l;
  char line[MAXLEN];
  int except, number, found;
  except = number = found = 0;

  int c;
  // 获取参数
  while (--argc > 0 && (*++argv)[0] == '-') {
    while ((c = *++*argv) != '\0') {
      switch (c) {
      case 'n':
        number = 1;
        break;
      case 'x':
        except = 1;
        break;
      default:
        printf("不支持命令：%c\n", c);
        argc = 0; /*终止循环*/
        found = -1;
        break;
      }
    }
  }
  //检查是否还剩余一个参数：匹配模板
  if (argc != 1) {
    printf("用于：./a.out [-x][-n] 模板");
  }
  // 根据参数显示结果
  else {
    while (get_line(line, MAXLEN) > 0) {
      lineno++;
      if ((strstr(line, *argv) != NULL) != except) {
        if (number)
          printf("%ld", lineno);
        printf("%s", line);
      }
    }
  }

  return found;
}

int get_line(char *s, int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    *s++ = c;
  if (c == '\n') {
    *s++ = c;
    i++;
  }
  *s = '\0';
  return i;
}
