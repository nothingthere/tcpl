/*改进atof函数，使其支持科学计数法，如`123.45e-6`，"e"可以是大写“E”。
*/

#include <ctype.h> // isspace, isdigit
#include <stdio.h>

double atof(char s[]);

int main(int argc, char const *argv[]) {
  char *lines[] = {"1.2e3", "12.2E-2", "1e10", "1e00", "", "1", "s1", "21s"};
  int count = 8;
  int i;
  for (i = 0; i < count; i++) {
    printf("\"%s\"\t： %f\n", lines[i], atof(lines[i]));
    // printf("%s\n", lines[i]);
  }

  return 0;
}

double atof(char s[]) {
  double val;        /*返回值*/
  int i;             /*索引*/
  int power;         /**/
  int sign;          /*正负号*/
  double expo = 1.0; /*科学计数法，10的次方数，> 0*/

  // 跳过空格
  for (i = 0; isspace(s[i]); i++)
    ;
  // 确定正负
  sign = s[i] == '-' ? -1 : 1;
  if (s[i] == '-' || s[i] == '+') {
    i++;
  }
  // 整数部分
  for (val = 0.0; isdigit(s[i]); i++) {
    val = val * 10.0 + (s[i] - '0');
  }
  //小数部分
  if (s[i] == '.') {
    i++;
  }
  for (power = 1.0; isdigit(s[i]); i++) {
    val = val * 10.0 + (s[i] - '0');
    power *= 10;
  }

  //科学计数法部分
  if (tolower(s[i]) == 'e') {
    i++;
    int sign, base;
    // 获取10的次方数
    sign = s[i] == '-' ? -1 : 1;
    if (s[i] == '-' || s[i] == '+') {
      i++;
    }
    for (base = 0; isdigit(s[i]); i++) {
      base = base * 10 + (s[i] - '0');
    }
    base *= sign;
    /*递归调用，不能处理科学计数法中还有科学计数法和小数的情况*/
    // base = (int)atof(s + i);
    // 计算次方
    if (base < 0) {
      for (i = base; i < 0; i++) {
        expo /= 10;
      }
    } else {
      for (i = base; i > 0; i--) {
        expo *= 10;
      }
    }
  }

  return sign * val / power * expo;
}
