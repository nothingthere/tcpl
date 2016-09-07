/*将C程序文件中的所有注释去除。需正确处理字符串和字符常量。
**** 仅仅是单行注释
*/
#include <stdio.h>
#define MAX_LEN 1000 /*假定一行文本最多有1000个字符*/

/*
获取一行文本
@line[]：字符串存入的数组
返回值：字符串长度，如果到文件结尾EOF，返回0
*/
int get_line(char line[]);

/*
去除每行中的单行注释
*/
void remove_commnet(char line[]);

int main(int argc, char const *argv[]) {
  int len;
  char line[MAX_LEN];
  while ((len = get_line(line)) > 0) {
    remove_commnet(line);
    printf("%s", line);
  }
  return 0;
}

/*去除单行注释*/

void remove_commnet(char line[]) { // qwdqwdqwdqwdqw
  int c, i;                        //
  for (i = 0; (c = line[i]) != '\0'; i++) {
    if (c == '/' && i >= 1 && line[i - 1] == '/') {
      line[i - 1] = '\n';
      line[1] = '\0';
      break;
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
