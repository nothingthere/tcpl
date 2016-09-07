/*打印文本字符统计表。*/

#include <stdio.h>
#define CHAR_NUM 0x7F /*一共有127个字符*/

int main(int argc, char const *argv[]) {
  int c, i;
  double chars[CHAR_NUM];
  // 初始化数组
  for (i = 0; i < CHAR_NUM; i++) {
    chars[i] = 0;
  }
  double total = 0; /*字符总数*/

  // 读取字符，记录数量
  while ((c = getchar()) != EOF) {
    chars[c]++;
    total++;
  }
  // 打印结果
  printf("字符总数：%.0f\n", total);
  printf("字符\t出现次数\t出现频率\n");
  for (i = 0; i < CHAR_NUM; i++) {
    if ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'z') ||
        (i >= 'A' && i <= 'Z')) { /*如果是0-9a-zA-Z正常显示*/
      putchar(i);
    } else if (i == ' ') { /*如果是空格、tab、换行和斜线另外表示*/
      printf("space");
    } else if (i == '\t') {
      putchar('\\');
      putchar('t');
    } else if (i == '\n') {
      putchar('\\');
      putchar('n');
    } else if (i == '\\') {
      putchar('\\');
      putchar('\\');
    } else { /*其它使用ASCII码表示*/
      printf("%d", i);
    }
    printf("\t%.0f\t%.6f%%\n", chars[i], chars[i] / total * 100);
  }
  return 0;
}
