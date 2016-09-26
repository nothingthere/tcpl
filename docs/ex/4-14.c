/*定义宏swap(t,x,y)，交换两个类型为t的参数的值。（使用块结构实现更容易）*/
#include <stdio.h>

#define swap(t, x, y)                                                          \
  {                                                                            \
    t tmp;                                                                     \
    tmp = x;                                                                   \
    x = y;                                                                     \
    y = tmp;                                                                   \
  }

int main(int argc, char const *argv[]) {
  int x = 0;
  int y = 10;
  printf("x=%d y=%d\n", x, y);
  swap(int, x, y);
  printf("交换后：\n");
  printf("x=%d y=%d\n", x, y);

  return 0;
}
