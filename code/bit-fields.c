#include <stdio.h>

#define KEYWORD 01
#define EXTERN 02
#define STATIC 04

typedef struct {
  size_t is_keyword : 1;
  size_t is_extern : 1;
  // size_t : 31;
  size_t is_static : 1;
} Word;

Word x;

void word_init(Word word) {
  word.is_keyword = 0;
  word.is_extern = 0;
  word.is_static = 0;
}

void keyword_toggle(Word *word) { word->is_keyword = word->is_keyword ? 0 : 3; }
void extern_toggle(Word *word) { word->is_extern = word->is_extern ? 0 : 1; }
void static_toggle(Word *word) { word->is_static = word->is_static ? 0 : 1; }

void word_print(Word word) {
  printf("字段情况：");
  if (word.is_extern)
    printf("extern ");
  if (word.is_keyword)
    printf("keyword ");
  if (word.is_static)
    printf("static ");
  printf("\n");
}
int main(int argc, char const *argv[]) {

  unsigned char flags = 0;

  flags |= (EXTERN | STATIC);

  Word word;
  // unsigned *x = &word.is_keyword;

  printf("Word位字段大小：%lu\n", sizeof(word));

  word_init(word);
  word_print(word);

  keyword_toggle(&word);
  extern_toggle(&word);
  static_toggle(&word);
  word_print(word);

  // keyword_toggle(&word);
  extern_toggle(&word);
  // static_toggle(&word);
  word_print(word);

  return 0;
}
