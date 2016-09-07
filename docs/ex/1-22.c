/*编写名为fold的程序，将一行文本折叠。在n列前的空字符前折叠，确保可以处理相当长的行，和在n列前没有空字符的情况。*/

/*
测试文本
12345 6 7 8 9

*/
#include <stdio.h>
#define MAX_LEN 1000 /*假定一行文本最多有1000个字符*/

/*
在@column处将@line行换行，
如果@column处不是空白字符，则在上一个空白字符处换行
*/
void fold(char line[], int column);
void fold2(char line[], int column);

void print_buffer(char line[], int n);

/*
获取一行文本
@line[]：字符串存入的数组
返回值：字符串长度，如果到文件结尾EOF，返回0
*/
int get_line(char line[]);

int main(int argc, char const *argv[]) {
  int len;
  char line[MAX_LEN];
  while ((len = get_line(line)) > 0) {
    fold2(line, 10);
    printf("%s", line);
  }
  return 0;
}

/*这样写直接改变原来的数组，不仅仅是简单的打印*/
void fold2(char line[], int column) {
  int i, c;
  int t;
  int location;
  for (i = 0, location = 0; (c = line[i]) != '\0'; i++) {
    location++;
    if (c == ' ') {
      t = i;
      // printf("t=%d\n", t);
    }
    if (location == column) {
      line[t] = '\n';
      location = 0;
    }
  }
}

/*日了够啦，下面我写的简直太复杂了*/
void print_buffer(char buffer[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%c", buffer[i]);
  }
}

void fold(char line[], int column) {
  int i, c;
  int place; /*上一个空白字符出现的位置*/
  place = -1;
  char buffer[column]; /*记录当前读取的字符*/
  int j;               /*buffer 的下标*/
  int k;               /*辅助循环变量*/

  for (i = 0, j = 0; (c = line[i]) != '\0'; i++) {

    if (j == column - 1) { /*达到了指定列数的字符数量*/

      /*如果到达指定列数的整数倍*/
      // printf("开始折叠\n");
      if (c == ' ' || c == '\t') { /*如果刚好是空白字符, 换行*/
        // printf("恰好打印\n");
        print_buffer(buffer, j); /*打印buffer*/
        printf("%c", '\n');
        j = 0;      /*清空buffer*/
        place = -1; /*重置在buffer中记录的空白字符位置*/

      } else { /*达到该行，但此处不是空白字符*/
               /*1 234 5 6abc de 7 8 9*/

        if (place == -1) { /*即使达到该列时，还没有一个空字符*/
          // printf("即使达到该列时，还没有一个空字符\n");
          print_buffer(buffer, j); /*打印buffer*/
          printf("%c", '\n');
          j = 0;      /*清空buffer*/
          place = -1; /*重置在buffer中记录的空白字符位置*/

        } else {
          // printf("没打印完全，还留有字符\n");
          print_buffer(buffer, place);
          printf("%c", '\n');
          for (k = 0; k < j - place - 1; k++) {
            /*将没有打印出来的字符，重新放在buffer开头*/
            buffer[k] = buffer[place + 1 + k];
          }
          j = k; /*将buffer的下标置于新的开始*/
          // printf("%d缓存当前不是空白字符的字符: %c\n", j, c);
          place = -1;
          //缓存当前不是空白字符的字符
          buffer[j] = c;
          j++;
        }
      }

    } else { /*没达到指定列前，仅将字符缓存到buffer中*/
      buffer[j] = c;
      // printf("%d:缓存=%c\n", j, c);
      // printf("place=%d\n", place);
      if (c == ' ' || c == '\t') { /*记录上一个空白字符出现的位置*/
        place = j;
        // printf("place=%d\n", place);
      }
      j++;
    }
  }

  /*打印残余字符*/
  // printf("文本结束，打印残留字符\n");
  if (j > 0) {
    print_buffer(buffer, j);
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
