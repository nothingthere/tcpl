/*
month_day：根据在当年的天数计算所处月份和号数
day_of_year：根据月份和号数计算所在当年的天数
*/

#include <stdio.h>

#define IS_LEAP(year)                                                          \
  (((year) % 4 == 0 && (year) % 100 != 0) || (year) % 400 == 0)

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(int argc, char const *argv[]) {
  int year = 2016;
  int yearday = 364;
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
  int i;
  int leap = IS_LEAP(year);
  for (i = 1; i < month; i++) {
    day += daytab[leap][i];
  }
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i;
  int leap = IS_LEAP(year);
  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}
