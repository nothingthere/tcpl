/*定义espace(s, t)程序，将字符串t复制到s中，不过需将不可见字符如`'\t'`和` '
 * \n'`等转换为可见形式，如`\t`和`\n`；也定义unescape(s,t)函数，与前者相反。
*/

#include <stdio.h>
#define ESPACE s[j++] = '\\';

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int main(int argc, char const *argv[]) {
  char text1[] = "i\nhave\ta\rdream\b!\\\"";
  char text2[1000]; /*长度不好判断，所以足够长就好*/
  char text3[1000]; /*长度不好判断，所以足够长就好*/
  printf("原字符串：\n%s\n", text1);
  escape(text2, text1);
  printf("\nespace后：\n%s\n", text2);
  unescape(text3, text2);
  printf("\nunescape后：\n%s\n", text3);
  // int i;
  // for (i = 0; i <= 0x1F; i++) {/*控制字符的取值范围0-0x1F*/
  //   if (i == '\n')
  //     printf("%c\n", i);
  // }
  return 0;
}

/*处理的转义字有：\n \t \r \b \\ \"*/

void escape(char s[], char t[]) {
  int i, j, c;
  for (i = 0, j = 0; (c = t[i]) != '\0'; i++, j++) {
    switch (c) {
    case '\n':
      s[j++] = '\\';
      s[j] = 'n';
      break;
    case '\t':
      s[j++] = '\\';
      s[j] = 't';
      break;
    case '\r':
      s[j++] = '\\';
      s[j] = 'r';
      break;
    case '\b':
      s[j++] = '\\';
      s[j] = 'b';
      break;
    case '\\':
      s[j++] = '\\';
      s[j] = '\\';
      break;
    case '\"':
      s[j++] = '\\';
      s[j] = '"';
      break;
    default:
      /*非特殊字符*/
      s[j] = c;
      break;
    }
  }

  /*最后一个\0字符*/
  s[j] = '\0';
}
void unescape(char s[], char t[]) {

  int i, j, c;
  for (i = 0, j = 0; (c = t[i]) != '\0'; i++, j++) {
    if (c == '\\') { /*如果开始有转义字符*/
      switch (t[++i]) {
      case 'n':
        s[j] = '\n';
        break;
      case 't':
        s[j] = '\t';
        break;
      case 'r':
        s[j] = '\r';
        break;
      case 'b':
        s[j] = '\b';
        break;
      case '\\':
        s[j] = '\\';
        break;
      case '"':
        s[j] = '\"';
        break;
      default: /*t中前一个字符是 \, 但当前字符不包含在处理的转义字符内*/
        s[j++] = '\\';
        s[j] = t[i];
        break;
      }

    } else { /*正常字符*/
      s[j] = t[i];
    }
  }

  /*最后的\0空字符*/
  s[j] = '\0';
}
