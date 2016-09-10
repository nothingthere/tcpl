
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// void prompt(void);
// int shuriqi(void);
// int max_day(int nian, int yue);
// int ruen(int nian);

int main(int argc, char const *argv[]) {

  time_t rawtime;
  struct tm *timeinfo;
  char buffer[9];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer), "%Y%m%d", timeinfo);
  puts(buffer);

  return 0;
}

char *riqi(void) {}
int shuriqi(void) {
  int riqi;
  int nian;
  int yue;
  int ri;

  printf("请输入年月日,格式应为20160812：\n"); //输入日期的提示
  scanf("%d", &riqi);                          //从终端输入日期

  nian = riqi / 10000;      /*年份*/
  yue = riqi % 10000 / 100; /*月份*/
  ri = riqi % 100;          /*几号*/

  int day = max_day(nian, yue);

  if (ruen(nian)) { /*闰年*/
    if ((0 < nian && nian < 10000) && (0 < yue && yue < 13) &&
        (0 < ri && ri < day)) {
      return riqi;
    } else {
      prompt();
      return shuriqi();
    }
  } else { /*不闰年*/
    if ((0 < nian < 10000) && (0 < yue && yue < 13) && (0 < ri && ri < day)) {
      printf("正确输入的结果为：%d\n", riqi);
      return riqi;
    } else {
      prompt();
      return shuriqi();
    }
  }
}

// 重输提示
void prompt(void) {
  // system("cls");
  printf("输入的日期格式不正确，请重新输入！\n");
  // system("pause");
}

// 判断闰年
int ruen(int nian) {
  return (nian % 4 == 0 && nian % 100 != 0) || (nian % 400 == 0);
}

// 获取每月最多天数
int max_day(int nian, int yue) {
  int ping[] = {31, 28, 31, 30, 31, 30,
                31, 31, 30, 31, 30, 31}; //定义平年的每月天数
  int buping[] = {31, 29, 31, 30, 31, 30,
                  31, 31, 30, 31, 30, 31}; //定义闰年的每月天数
  int day;

  if (ruen(nian)) {
    day = buping[yue - 1];
  } else {
    day = ping[yue - 1];
  }
  return day;
}
