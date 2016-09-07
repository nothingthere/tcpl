/*编写名为entab的程序，将空格尽可能替换为tab。*/

#include <stdio.h>
#define MAX_LEN 1000 /*假定一行文本最多有1000个字符*/

/*
获取一行文本
@line[]：字符串存入的数组
返回值：字符串长度，如果到文件结尾EOF，返回0
*/
int get_line(char line[]);

/*
将空格尽可能多地转换为tab
@n：几个空格=1个tab
*/
void entab(char line[], int n);

int main(int argc, char const *argv[]) {
  char line[MAX_LEN];
  while (get_line(line) > 0) {
    entab(line, 4);
  }
  return 0;
}

void entab(char line[], int n) {
  int i, j, c;
  int inspace = 0; /*是否开始有空格*/
  int spaces = 0;  /*当前空格数*/
  int p, q;        /*整除的整数和余数*/

  for (i = 0; (c = line[i]) != '\0'; i++) {
    if (c == ' ') {
      inspace = 1;
      spaces++;
    } else {
      inspace = 0;
      p = spaces / n;
      q = spaces % n;
      for (j = 0; j < p; j++) { /*打印tab*/
        printf("\\t");
      }
      for (j = 0; j < q; j++) { /*打印剩余空格*/
        printf("\\space");
      }
      spaces = 0; /*重置空格数*/
      printf("%c", c);
    }
  }
}
int get_line(char line[]) {
  int i, c;
  for (i = 0; i < MAX_LEN - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
    line[i] = c;
  }
  if (c == '\n') {
    line[i] = '\n';
    i++;
  }
  line[i] = '\0';
  return i;
}
