/*定义my_htoi(s)函数，将16进制字符串（以0x或0X开始）转换为整数。*/

#include <ctype.h>
#include <stdio.h>
#define MAX_LEN 1000

int get_line(char line[], int lim);
int my_htoi(char line[]);

int main(int argc, char const *argv[]) {
  int i;
  char line[MAX_LEN];
  // printf("%d\n", 0xf1);
  while ((i = get_line(line, MAX_LEN)) > 0) {
    printf("\t--> %d\n", my_htoi(line));
  }
  return 0;
}

int my_htoi(char line[]) {
  int i, n, c;
  /*去除前置空格*/
  for (i = 0; isspace(line[i]); i++)
    ;
  /*判断是否符合16进制数格式*/
  if (line[i] != '0' || tolower(line[i + 1]) != 'x') {
    printf("不是16进制格式\n");
    return 0;
  }

  i++, i++;

  /*开始计算16进制数*/
  printf("i=%d c=%c\n", i, line[i]);
  for (n = 0; c = line[i], isxdigit(c); i++) {
    if (isdigit(c)) { /*0...9*/

      n = 16 * n + (c - '0');
    } else { /*a...f*/
      n = 16 * n + (10 + (c - 'a'));
    }
  }

  return n;
}

int get_line(char line[], int lim) {
  int c, i;
  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }
  if (c == '\n') {
    line[i] = '\n';
    i++;
  }
  line[i] = '\0';
  return i;
}
