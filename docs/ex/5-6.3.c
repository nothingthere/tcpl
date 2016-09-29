/*指针版my_itoa
将整数转换为字符串
*/

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_itoa(int n, char *s);
void my_itoa2(int n, char *s);
void reverse(char *s);

int main(int argc, char const *argv[]) {
  int nums[] = {0, 12, -2323, INT_MIN, INT_MAX};
  int count = 5;
  char line[20 + 1 + 1];
  int i;
  for (i = 0; i < count; i++) {
    my_itoa2(nums[i], line);
    printf("%12d: \"%s\"\n", nums[i], line);
  }
  return 0;
}

void reverse(char *s) {
  char *t = s + strlen(s) - 1;
  while (s < t) {
    *s ^= *t ^= *s ^= *t;
    s++, t--;
  }
}

void my_itoa(int n, char *s) {
  char *t = s;
  int sign = n;
  do {
    *s++ = abs(n % 10) + '0';
  } while (n /= 10);
  if (sign < 0) {
    *s++ = '-';
  }
  *s = '\0';
  reverse(t);
}

// ????????????????
void my_itoa2(int n, char *s) {
  if (n < 0) {
    *s++ = '-';
  }

  if (n / 10) {
    my_itoa2(abs(n / 10), s + 1);
  } else {
    *s = '\0';
  }
  *s = abs(n % 10) + '0';
}
