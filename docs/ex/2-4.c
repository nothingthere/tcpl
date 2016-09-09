/*定义函数squeeze(s1, s2)，将字符串s2中有s1中的任何字符都删除*/

#include <stdio.h>

void squeeze(char line1[], char line2[]);

int main(int argc, char const *argv[]) {
  char s1[] = "i have a dream";
  char s2[] = "iaveadrea ";

  printf("原字符串：%s\n", s1);
  squeeze(s1, s2);
  printf("操作后  ：%s\n", s1);
  return 0;
}

void squeeze(char line1[], char line2[]) {
  int i, j, k;
  int c1, c2;
  for (k = 0; (c2 = line2[k]) != '\0'; k++) { /*历遍line2中的每一个字符*/
    // printf("c2=%c\n", c2);
    /*历遍line1，删除其中当前出现的line1中的字符*/
    for (i = 0, j = 0; (c1 = line1[i]) != '\0'; i++) {
      // printf("c1=%c\n", c1);
      if (c1 != c2) {
        line1[j++] = c1;
      }
    }
    line1[j] = '\0';
  }
}
