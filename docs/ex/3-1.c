/*改写binsearch函数，循环内有2个条件判断，改写为1个判断。（循环外判断会增加）。
*/
#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(int argc, char const *argv[]) {
  // printf("main\n");
  int nums[] = {1, 2, 3, 4, 5, 6, 7};
  int i;
  // printf("%d\n", binsearch(4, nums, 7));
  for (i = 1; i <= 7; i++) {
    printf("%d @ %d\n", i, binsearch(i, nums, 7));
  }
  return 0;
}

int binsearch(int x, int v[], int n) {
  int low, high, mid;
  low = 0;
  high = n - 1;
  mid = (low + high) / 2;
  while (low <= high && x != v[mid]) {
    mid = (low + high) / 2;
    printf("low=%d high=%d mid=%d\n", low, high, mid);
    if (x < v[mid]) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return (x = v[mid]) ? mid : -1;
}
