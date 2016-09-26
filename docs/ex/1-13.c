/*打印文本单词长度统计表。*/

#include <stdio.h>

#define IN 1        /*在单词内*/
#define OUT 0       /*在单词外*/
#define MAX_LEN 100 /*假设单词长度不超过100*/

int main(int argc, char const *argv[]) {
  int c, i;
  double words[MAX_LEN]; /*存储单词长度的数组*/
  double total = 0;      /*单词总数*/
  // 初始化数组
  for (i = 0; i < MAX_LEN; i++) {
    words[i] = 0;
  }
  int len = 0; /*记录单词长度*/
  int state = OUT;

  // 循环统计
  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') { //不在单词中
      state = OUT;
      words[len]++;
      total++;
      len = 0;                 /*重置长度*/
    } else if (state == OUT) { //开始进入单词
      state = IN;
      len++;
    } else { //在单词中
      len++;
    }
  }
  // 打印结果
  printf("长度\t次数\t频率\n");
  for (i = 1; i < MAX_LEN; i++) {
    if (words[i] > 0) {
      printf("%d\t%.0f\t%.5f%%\n", i, words[i], words[i] / total * 100);
    }
  }
  return 0;
}
