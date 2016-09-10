#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(int argc, char const *argv[]) {
  // printf("main\n");
  int nums[] = {1, 2, 3, 4, 5, 6, 7};
  int i;
  // printf("%d\n", binsearch(4, nums, 7));
  for (i = 1; i <= 7; i++) {
    printf("%d\n", binsearch(i, nums, 7));
  }
  return 0;
}

int binsearch(int x, int v[], int n) {
  int low, high, mid;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    // printf("low=%d high=%d mid=%d\n", low, high, mid);
    if (x < v[mid]) {
      high = mid - 1;
    } else if (x > v[mid]) {
      low = mid + 1;
    } else {
      return mid;
    }
  }

  return -1;
}
