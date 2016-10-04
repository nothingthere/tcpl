
/*
简化版UNIX的echo命令
使用指针
*/

#include <stdio.h>

int main(int argc, char const *argv[]) {
  // int i;
  // for (i = 1; i < argc; i++)
  // printf("%s%s", argv[i], i < argc - 1 ? " " : "");
  while (--argc)
    printf(argc > 1 ? "%s " : "%s", *++argv);
  // printf("%s%s", *++argv, argc > 1 ? " " : "");
  printf("\n");
  return 0;
}
