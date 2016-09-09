/*定义函数any(s1,s2)，返回s1中出现s2中任意字符的位置，如果没有，返回-1*/

#include <stdio.h>
#include <string.h>
int any(char line1[], char line2[]);

int main(int argc, char const *argv[]) {
  char line1[] = "i have a dream";
  char line2[] = "awedw";

  printf("strpbrk：%s\n", strpbrk(line1, line2)); /*???返回不正确？？？*/
  printf("any    ：%d\n", any(line1, line2));
  return 0;
}

int any(char line1[], char line2[]) {
  int i, j;
  int c1, c2;
  for (i = 0; (c2 = line2[i]) != '\0'; i++) {   /*历遍line2*/
    for (j = 0; (c1 = line1[j]) != '\0'; j++) { /*历遍line1*/
      if (c1 == c2) {
        return j;
      }
    }
  }
  return -1;
}
