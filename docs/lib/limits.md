# limits.h

定义了整型数据的取值范围。

## 字符变量char（8Char）

- CHAR_BIT：一个字符所占位数。8
- CHAR_MAX：字符变量的最大取值。127
- CHAR_MIN：字符变量的最小取值。-128
- UCHAR_MAX：字符变量不带符号的最大取值。255
- SCHAR_MAX：字符变量带符号的最大取值。+127
- SCHAR_MIN：字符变量带符号的最小取值。-128

## 短整型short int（16Short）

- SHRT_MAX：短整型大取值。32767
- SHRT_MIN：短整型小取值。-32768
- USHRT_MAX：短整型不带符号的最大值。65535

## 整型变量int（32Int）

- INT_MAX：整型变量最大值。2147483647（21亿...）
- INT_MIN：整型变量最小值。-2147483648
- UINT_MAX：整型不带符号的最大取值。4294967295

## 长整型long int（64Long）

- LONG_MAX：长整型最大取值。9223372036854775807
- LONG_MIN：长整型最小取值。-9223372036854775808
- ULONG_MAX：长整型不带符号最大取值。18446744073709551615

## 测试

```c
#include <limits.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("char字节数：%ld\n", sizeof(char));
    printf("short字节数：%ld\n", sizeof(short));
    printf("int字节数：%ld\n", sizeof(int));
    printf("long字节数：%ld\n", sizeof(long));

  printf("\n字符型字节：%ld\n", sizeof(char));
  printf("短整型字节：%ld\n", sizeof(short int));
  printf("整型字节：%ld\n", sizeof(int));
  printf("长整型字节：%ld\n", sizeof(long int));

  printf("\n字符变量char：\n");
  printf("一个字符所占位数：%d\n", CHAR_BIT);
  printf("字符变量的最大取值：%d\n", CHAR_MAX);
  printf("字符变量的最小取值：%d\n", CHAR_MIN);
  printf("字符变量不带符号的最大取值：%d\n", UCHAR_MAX);
  printf("字符变量带符号的最大取值：%d\n", SCHAR_MAX);
  printf("字符变量带符号的最小取值：%d\n", SCHAR_MIN);

  printf("\n短整型short int：\n");
  printf("短整型大取值：%d\n", SHRT_MAX);
  printf("短整型小取值：%d\n", SHRT_MIN);
  printf("短整型不带符号的最大值：%d\n", USHRT_MAX);

  printf("\n整型变量int：\n");
  printf("整型变量最大值：%d\n", INT_MAX);
  printf("整型变量最小值：%d\n", INT_MIN);
  printf("整型不带符号的最大取值：%ld\n", UINT_MAX); //??

  printf("\n长整型long int：\n");
  printf("长整型最大取值：%ld\n", LONG_MAX);
  printf("长整型最小取值：%ld\n", LONG_MIN);
  printf("长整型不带符号最大取值：%ul\n", ULONG_MAX); //??

  return 0;
}
```
