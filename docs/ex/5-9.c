/*用指针替换下标方法重新实现day_of_year和month_day函数。*/

#include <stdio.h>
#include <stdlib.h>
#define IS_LEAP(year)                                                          \
  (((year) % 4 == 0 && (year) % 100 != 0) || (year) % 400 == 0)

char tab0[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char tab1[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *daytab[] = {tab0, tab1};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(int argc, char const *argv[]) {
  int year = 2016;
  int yearday = 367;
  int month, day;

  month_day(year, yearday, &month, &day);

  printf("%d年：%s\n", year, IS_LEAP(year) ? "闰年" : "不闰年");
  printf("%d年的第%d天是：%d月%d号\n", year, yearday, month, day);

  printf("%d年的%d月%d号是当年的第：%d天\n", year, month, day,
         day_of_year(year, month, day));

  int month2 = 9;
  int day2 = 29;
  printf("\n%d年的%d月%d号是当年的第：%d天\n", year, month2, day2,
         day_of_year(year, month2, day2));
  return 0;
}

int day_of_year(int year, int month, int day) {
  int leap = IS_LEAP(year);
  int i;
  char *p = *(daytab + leap);

  // 错误检查
  if (year <= 0 || month <= 0 || month > 12 || day <= 0 || day > p[month])
    return -1;
  // 错误检查结束

  for (i = 1; i < month; i++)
    day += p[i];
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int leap = IS_LEAP(year);
  int i;
  char *p = *(daytab + leap);
  int total_days = leap ? 366 : 365;
  // 错误检查
  if (year <= 0 || yearday <= 0 || yearday > total_days) {
    printf("error\n");
    exit(1);
  }
  // 错误检查结束

  for (i = 1; yearday > p[i]; i++)
    yearday -= p[i];
  *pmonth = i;
  *pday = yearday;
}
