
/*
gerp命令，使用命令行参数
添加反转-x和打印行号-n功能
新添了忽略大小写的功能
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

int get_line(char *line, int lim);
void str_lower(char *s);

int main(int argc, char const *argv[]) {
  char line[MAXLEN];
  char tmp_line[MAXLEN]; /*不区分大小写时的中间变量*/
  char pattern[MAXLEN];
  int found = 0;
  int c;
  const char *p;
  int except, number, ignore_case;
  long lineno = 0l;
  except = number = ignore_case = 0;

  // 获取参数
  while (--argc > 0 && (*++argv)[0] == '-') {
    p = *argv;
    while ((c = *++argv[0]) != '\0') {
      switch (c) {
      case 'x':
        except = 1;
        break;
      case 'n':
        number = 1;
        break;
      case 'i':
        ignore_case = 1;
        break;
      default:
        printf("参数错误：%c\n", c);
        argc = 0;
        found = -1;
        break;
      }
    }
  }

  // 判断是否还剩下一个参数，即模板

  if (argc != 1) {
    printf("用法：a.out -n -x 模板 < 文件\n");
    return -1;
  }

  strcpy(pattern, *argv);
  // printf("pattern：\"%s\"\n", pattern);
  if (ignore_case) {
    // printf("isdigit\n");
    str_lower(pattern);
  }
  // 根据参数显示结果
  while (get_line(line, MAXLEN) > 0) {
    lineno++;
    strcpy(tmp_line, line);
    if (ignore_case) {
      str_lower(tmp_line);
    }
    // printf("tmp_line：\"%s\"\n", tmp_line);
    if ((strstr(tmp_line, pattern) != NULL) != except) { /*牛逼*/
      if (number)
        printf("%ld", lineno);
      printf("%s", line);
      found++;
    }
    // if (strstr(line, *argv) == NULL && except) {
    //   if (number)
    //     printf("%ld", lineno);
    //   printf("%s", line);
    // }
  }

  return found;
}

int get_line(char *line, int lim) {
  int i, c;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    *line++ = c;
  }
  if (c == '\n') {
    *line++ = c;
    i++;
  }
  *line = '\0';
  return i;
}

void str_lower(char *s) {
  while (*s) {
    *s = tolower(*s);
    s++;
  }
}
