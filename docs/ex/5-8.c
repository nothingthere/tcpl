/*day_of_year和month_day都没有错误检查，尝试修改。*/

#include <stdio.h>
#include <stdlib.h>

#define IS_LEAP(year)                                                          \
  (((year) % 4 == 0 && (year) % 100 != 0) || (year) % 400 == 0)

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(int argc, char const *argv[]) {
  int year = 2016;
  int yearday = 366;
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

  // 错误检查
  /*
  month：不超过12
  day：根据月份判断所在月份天数是否超过最大值
  */
  if (month <= 0 || month > 12) {
    printf("error：月份超过12或<=0：%d\n", month);
    exit(1);
  }
  if (day <= 0 || daytab[leap][month] < day) {
    printf("error：%d月天数不能超过%d天或<=0：%d\n", month, daytab[leap][month],
           day);
    exit(1);
  }
  // 错误检查结束

  for (i = 1; i < month; i++) {
    day += daytab[leap][i];
  }
  return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
  int i;
  int leap = IS_LEAP(year);

  // 错误检查
  /*
  一年中的天数闰年不超过366天，不闰年不超过365天
  */
  if (yearday <= 0) {
    printf("error：一年的天数不能%d<=0\n", yearday);
    exit(1);
  }

  if (leap && yearday > 366) {
    printf("error：%d年天数不能超过366天：%d\n", year, yearday);
    exit(1);
  }
  if (!leap && yearday > 365) {
    printf("error：%d年天数不能超过365天：%d\n", year, yearday);
    exit(1);
  }
  // 错误检查结束

  for (i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
  *pday = yearday;
}
