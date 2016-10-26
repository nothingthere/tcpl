#include <stdio.h>

typedef union u_tag {
  int ival;
  float fval;
  char *sval;
} Utag;

typedef struct symbol {
  char *name;
  int flags;
  int utype;
  Utag u;
} Symbol;

enum { INT, FLOAT, STRING };

Symbol symbol;

#define NSYM 100
struct {
  char *name;
  int flags;
  int utype;
  union {
    int ival;
    float fval;
    char *sval;
  } u;
} symtab[NSYM];

void print_symbol(Symbol symbol) {
  int utype = symbol.utype;
  printf("name=\"%s\"\n", symbol.name);
  printf("union=");
  switch (utype) {
  case INT:
    printf("%d\n", symbol.u.ival);
    break;
  case FLOAT:
    printf("%f\n", symbol.u.fval);
    break;
  default:
    printf("\"%s\"\n", symbol.u.sval);
    break;
  }
}

int main(int argc, char const *argv[]) {

  symbol.name = "claudio";

  symbol.u.ival = 1;
  symbol.utype = INT;

  symbol.u.fval = 1.11f;
  symbol.utype = FLOAT;

  symbol.u.sval = "nothingthere";
  symbol.utype = STRING;

  print_symbol(symbol);

  return 0;
}
