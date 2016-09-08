/*
@Gregory Pietsch
测试wc.c字符数，单词数，行数统计程序
0. 创建空文件
1. 创建文件，只有一行，但字符量很大
2. 创建文件，只有空格，无换行
3. 创建文件，只有换行
4. 创建文件，。。。。
*/

#include <assert.h>
#include <stdio.h>
int main(int argc, char const *argv[]) {
  FILE *f;
  unsigned long i;
  static char *ws = " \f\t\v";
  static char *al = "abcdefghijklmnopqrstuvwxyz";
  static char *i5 = "a b c d e f g h i j k l m "
                    "n o p q r s t u v w x y z "
                    "a b c d e f g h i j k l m "
                    "n o p q r s t u v w x y z "
                    "a b c d e f g h i j k l m "
                    "n\n";
  // 0. 创建空文件
  f = fopen("test0", "w");
  assert(f != NULL);
  fclose(f);
  // 1. 创建文件，只有一行，但字符量很大
  f = fopen("test1", "w");
  assert(f != NULL);
  for (i = 0; i < ((66000ul / 26) + 1); i++) {
    fputs(al, f);
  }
  fclose(f);
  return 0;
}
