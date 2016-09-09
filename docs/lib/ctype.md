# ctype.h

## 字符判断函数

-   isalnum(c)：isapha(c) || isdigit(c)
-   isalpha(c)：isupper(c) || islower(c)
-   iscntrl(c)：控制字符
-   isdigit(c)：数字字符
-   isgraph(c)：除空格外，可打印字符
-   islower(c)：小写字母
-   isprint(c)：含空格，可打印字符
-   ispunct(c)：除空格、字母和数字字符外，可打印字符。`! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _` { | } ~ \`。
-   isupper(c)：大写字母
-   isxdigit(c)：16进制数字字符。`0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f`

可打印字符的范围为0x20(' ')到0x7E('-')；控制字符为0（NUL）到0x1F(US)，以及0x7F(DEL)。

```c
#include <ctype.h>
#include <stdio.h>

int main(void) {
  int i;
  printf("所有字符：");
  for (i = 0; i < 128; i++) {
    printf("%c ", i);
  }
  printf("\n");

  printf("符号字符：");
  for (i = 0; i < 128; i++) {
    if (ispunct(i)) {
      printf("%c ", i);
    }
  }
  printf("\n");

  printf("16进制数字字符：");
  for (i = 0; i < 128; i++) {
    if (isxdigit(i)) {
      printf("%c ", i);
    }
  }
  printf("\n");

  printf("控制字符：");
  for (i = 0; i < 128; i++) {
    if (iscntrl(i)) {
      printf("%c ", i);
    }
  }
  printf("\n");

  return 0;
}
```

## 字符转换函数

-   int tolower(c)：如果c为大写，返回小写，否则返回c。
-   int toupper(c)：如果c为小写，返回大写，否则返回c。
