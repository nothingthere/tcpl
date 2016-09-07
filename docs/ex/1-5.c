#include <stdio.h>

/*使用for语句改写华氏度-摄氏度转化表
华氏度从300->0
*/
int main(int argc, char const *argv[]) {
  int fahr;
  for (fahr = 300; fahr >= 0; fahr = fahr - 20) {
    printf("%d\t%6.2f\n", fahr, (5.0 / 9.0) * (fahr - 32));
  }
  return 0;
}
