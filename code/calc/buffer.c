#include "calc.h"
#include <stdio.h>

#define BUFFERSIZE 100
static int buffer[BUFFERSIZE];
static int bufp = 0;

int getch(void) { return (bufp > 0) ? buffer[--bufp] : getchar(); }
void ungetch(int c) {
  if (bufp < BUFFERSIZE) {
    buffer[bufp++] = c;
  } else {
    printf("error：buffer已满\n");
  }
}
