#include <stdio.h>

int main(int argc, char const *argv[]) {
  float fahr;
  float lower, upper, step;
  lower = 0;
  upper = 300;
  step = 20;

  printf("华氏度\t摄氏度\n");
  for (fahr = lower; fahr <= upper; fahr += step) {
    printf("%.0f\t%.2f\n", fahr, (fahr - 32) * 5 / 9);
  }

  return 0;
}
