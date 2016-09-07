# float.h

## 浮点型

-   FLT_RADIX：？指数表示的基数。2
-   FLT_ROUNDS：加法的舍入规则。1
-   FLT_DIG：float类型精度（小数点后位数）。6
-   FLT_EPSILON：使用"1.0+x!=1.0"成立的最小值x。1.192093e-07
-   FLT_MANT_DIG：？基数为FLT_RADIX的尾数中的数字。24
-   FLT_MAX：最大浮点数。3.402823e+38
-   FLT_MAX_EXP：使用FLT_RADIX^(n-1)可表示的最大n。128
-   FLT_MIN：最小浮点数。1.175494e-38
-   FLT_MIN_EXP：使用10^n可表示的最小n。-125

## 双精度浮点型

-   DBL_DIG：双精度浮点型的精度（小数点后位数）。15
-   DBL_EPSILON：使用\\"1.0+x!=1.0\\"成立的最小值x。2.220446e-16
-   DBL_MANT_DIG：？基数为FLT_RADIX的尾数中的数字。53
-   DBL_MAX：最大双精度浮点数。1.797693e+308
-   DBL_MAX_EXP：使用FLT_RADIX^(n-1)可表示的最大n。1024
-   DBL_MIN：最小双精度浮点数。2.225074e-308
-   DBL_MIN_EXP：使用10^n可表示的最小n。-1021

## 测试

```c
#include <float.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("浮点型所占字节数：%ld\n", sizeof(float));
  printf("双精度浮点型所占字节数：%ld\n", sizeof(double));
  printf("长双精度浮点型所占字节数：%ld\n", sizeof(long double));


  printf("\n浮点型float：\n");
  printf("？指数表示的基数：%d\n", FLT_RADIX);
  printf("加法的舍入规则：%d\n", FLT_ROUNDS);
  printf("float类型精度（小数点后位数）：%d\n", FLT_DIG);
  printf("使用\"1.0+x!=1.0\"成立的最小值x：%e\n", FLT_EPSILON);
  printf("？基数为FLT_RADIX的尾数中的数字：%d\n", FLT_MANT_DIG);
  printf("最大浮点数：%e\n", FLT_MAX);
  printf("使用FLT_RADIX^(n-1)可表示的最大n：%d\n", FLT_MAX_EXP);
  printf("最小浮点数：%e\n", FLT_MIN);
  printf("使用10^n可表示的最小n：%d\n", FLT_MIN_EXP);

  printf("\n双精度浮点型double：\n");
  printf("双精度浮点型的精度（小数点后位数）：%d\n", DBL_DIG);
  printf("使用\"1.0+x!=1.0\"成立的最小值x：%e\n", DBL_EPSILON);
  printf("？基数为FLT_RADIX的尾数中的数字：%d\n", DBL_MANT_DIG);
  printf("最大双精度浮点数：%e\n", DBL_MAX);
  printf("使用FLT_RADIX^(n-1)可表示的最大n：%d\n", DBL_MAX_EXP);
  printf("最小双精度浮点数：%e\n", DBL_MIN);
  printf("使用10^n可表示的最小n：%d\n", DBL_MIN_EXP);

  return 0;
}
```
