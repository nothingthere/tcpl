#include <stdio.h>
/*打印摄氏度-华氏度对照表
        for fahr=0,20,...,30*/

int main(int argc, char const *argv[]) {
  float fahr, celsius;
  float lower, upper, step;

  lower = 0;   /*最低摄氏度*/
  upper = 300; /*最高摄氏度*/
  step = 20;   /*梯度*/
  celsius = lower;

  printf("摄氏度\t华氏度\n");
  while (celsius <= upper) {
    fahr = (9.0 / 5.0) * (celsius + 32);
    printf("%.0f\t%6.2f\n", celsius, fahr);
    celsius = celsius + step;
  }
  return 0;
}
