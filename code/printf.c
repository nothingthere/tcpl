#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  char *s = "hello, world";
  char tmp[100];
  char *formats[] = {":%s:",    ":%10s:",  ":%.10s:",   ":%-10s:",
                     ":%.15s:", ":%-15s:", ":%15.10s:", ":%-15.10s:"};
  int formats_len = sizeof(formats) / sizeof(formats[0]);

  for (size_t i = 0; i < formats_len; i++) {
    printf("%-14s", formats[i]);
    sprintf(tmp, formats[i], s);
    // printf(formats[i], s);
    printf("%s", tmp);
    printf("\n");
  }
  // printf(":%-10s:\n", s);
  return 0;
}
