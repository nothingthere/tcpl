/*编写名为detab的程序，将文本中的tab字符用n个空格代替。*/

/*测试
@
@@@@@
    @
@@@@@@@@@
@		@
@@@@@@@@@@
*/
#include <stdio.h>
#define MAX_LEN 1000 /*假定一行文本最多有1000个字符*/

/*
@n：一个tab字符用多少个空格替换
@line[]：需改变的字符串
边将tab替换为空格边输出
*/
void detab(char line[], int n);

/*
获取一行文本
@line[]：字符串存入的数组
返回值：字符串长度，如果到文件结尾EOF，返回0
*/
int get_line(char line[]);

/*
统计一行文本中有几个tab，用于测试
@line[]；字符数组
*/

int tabs(char line[]);

int main(int argc, char const *argv[]) {
  char line[MAX_LEN];
  while (get_line(line) > 0) {
    detab(line, 4);
  }
  return 0;
}

void detab(char line[], int n) {
  int i, c;
  int j;
  for (i = 0; (c = line[i]) != '\0'; i++) {
    if (c == '\t') {
      for (j = 0; j < n; j++) {
        printf("%c", '@');
      }
    } else {
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
