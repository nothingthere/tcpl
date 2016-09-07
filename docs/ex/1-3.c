#include <stdio.h>
/*打印华氏度-摄氏度对照表
        for fahr=0,20,...,30*/

int main(int argc, char const *argv[]) {
  float fahr, celsius;
  float lower, upper, step;

  lower = 0;   /*最低华氏度*/
  upper = 300; /*最高华氏度*/
  step = 20;   /*梯度*/
  fahr = lower;

  printf("华氏度\t摄氏度\n");
  while (fahr <= upper) {
    celsius = (5.0 / 9.0) * (fahr - 32);
    printf("%.0f\t%6.2f\n", fahr, celsius);
    fahr = fahr + step;
  }
  return 0;
}
