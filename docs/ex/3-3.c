/*：定义expand(s1,  s2)函数,将s1中的缩写形式如a-z，膨胀后写入s2中如abc..xyz
。需处理数字，如a-z0-9，以及结尾或开头为-，如-z和a-。*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void expand(char s1[], char s2[]);
int main(int argc, char const *argv[]) {
  char *s[] = {"a-z-", "a-b-c", "a-z0-9", "-a-z",  "a",   "a-",    "-a", "-z",
               "z-a-", "-1-6-", "a-ee-a", "1-9-1", "5-5", "a-R-L", NULL};
  // char *s[] = {"a-z", NULL};
  char result[26 + 26 + 10 + 1];
  int i = 0;
  while (s[i]) {
    expand(s[i], result);
    printf("%s\t: %s\n", s[i], result);
    i++;
  }

  return 0;
}

/*
有4种情况可以扩张：a, a-, -z, a-z
记录上一个字符prev，和上一个字母数字字符，起始值都为\0
每读取一个字符，判断是否满足扩张条件，如果满足，记录起始head和终点tail，以及是否递增increase

扩张时分2种情况：递增 和 递减
扩张时需先检查可是是否正确：
    如果是字符，不能同数字扩张，不能小写和大写之间扩张
    如果是数字字符，不能同字母扩张
扩张完成后，将前一个字符prev和前一个字母字符都重置为\0，重新开始

如果不扩张，仅记录前一个字符prev，和前一个字母字数字字符prev_char
*/
void expand(char s1[], char s2[]) {
  int i;                /*s1下标*/
  int j;                /*s2下标*/
  int c;                /*当前字符*/
  int tmp;              /*中间量字符*/
  int prev_char = '\0'; /*上一个数字字母字符*/
  int prev = '\0';      /*上一个字符*/
  int seprator = '-';   /*分隔符*/
  int begin = 0;        /*知否开始扩张*/
  int head;             /*扩张起点*/
  int tail;             /*扩张的终点*/
  int increase;         /*知否递增扩张*/
  for (i = 0, j = 0; (c = s1[i]) != '\0'; i++) {
    // printf("prev=%c  prev_char=%c c=%c\n", prev, prev_char, c);
    // 默认开始扩张，递增扩张
    begin = 1;
    increase = 1; // -a -z 都为递增形式

    // 开始扩张的条件，满足条件时，记录head,tail和increase值得
    if (isalnum(c) && isalnum(prev_char) && prev == seprator) { /*完整a-z*/
      // printf("condition1\n");
      head = prev_char;
      tail = c;
      increase = (head < tail) ? 1 : 0;
    } else if (isalnum(c) && prev == seprator && prev_char == '\0') { /*-a*/
      // printf("condition2\n");
      tail = c;
      if (isdigit(c)) {
        head = '0';
      } else if (isupper(c)) {
        head = 'A';
      } else {
        head = 'a';
      }
    } else if (c == seprator && isalnum(prev) && s1[i + 1] == '\0') { /*a-*/
      // printf("condition3\n");
      head = prev;
      if (isdigit(prev)) {
        tail = '9';
      } else if (isupper(prev)) {
        tail = 'Z';
      } else {
        tail = 'z';
      }
    } else if (isalnum(c) && prev == '\0' &&
               s1[i + 1] == '\0') { /*a 不扩张单独的-字符*/
      head = tail = c;
    } else {
      begin = 0;
    }

    // 按照head, tail, 和increase变量扩张s2
    if (begin == 1) {
      // 错误检查
      if (isalpha(head)) {
        if (!isalpha(tail) || (isupper(head) && islower(tail)) ||
            (islower(head) && isupper(tail))) {
          fprintf(stderr, "%s格式不正确：%c %c\n", s1, head, tail);
          exit(1);
        }
      }

      if (isdigit(head) && !isdigit(tail)) {
        fprintf(stderr, "%s格式不正确：%c %c\n", s1, head, tail);
        exit(1);
      }
      // 正式扩张
      if (increase) { /*递增*/
        // printf("递增\n");
        for (tmp = head; tmp <= tail; tmp++) {
          s2[j++] = tmp;
        }
      } else { /*递减*/
        // printf("递减\n");
        for (tmp = head; tmp >= tail; tmp--) {
          s2[j++] = tmp;
        }
      }

      // 完成一次扩张，重新开始
      prev = '\0';
      prev_char = '\0';
    } else { /*不扩张，仅记录字符*/
      prev = c;
      if (isalnum(c)) {
        prev_char = c;
      }
    }
  }

  s2[j] = c; /*字符串最后的\0字符*/
}
